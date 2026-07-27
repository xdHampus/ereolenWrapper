# Cross-building for Kobo

Produces `libereolenwrapper.so` as an ARM Lua C module that KOReader's LuaJIT
can `require()` on a Kobo e-reader.

```sh
nix build .#kobo        # -> result/lib/libereolenwrapper.so
```

Every download is a fixed-output derivation, so the build itself runs offline
and the result is cached like any other package. The toolchain alone is 288 MB
unpacked and the first build takes a few minutes; after that only a change to
the wrapper's own sources causes a rebuild.

There is also `./build.sh`, which does the same thing outside Nix:

```sh
nix shell nixpkgs#cmake nixpkgs#pkg-config --command ./cross/kobo/build.sh
```

It fetches into `cross/kobo/work/` (gitignored) and is the quicker loop when
iterating on the cross build itself, since it reuses one build tree instead of
starting clean. Both paths share `kobo.cmake` and compile the wrapper with the
same flags — `-Wall -Wextra -O2 -std=gnu++20 -fPIC` — so they produce
equivalent binaries.

Two things the Nix path needs that a normal shell hides:

  * **binutils by name.** `kobo.cmake` sets `CMAKE_AR` and friends with `FORCE`.
    Creating an archive is arch-agnostic enough that the host's `ar` works, so
    a shell with binutils installed never notices they were never configured;
    a Nix build has no `ar` at all and fails at "Linking CXX static library"
    with `Error running link command: no such file or directory`. `FORCE` is
    needed because nixpkgs' CMake hook passes `-DCMAKE_AR="$(command -v $AR)"`,
    which under `stdenvNoCC` expands to an empty string and seeds the cache
    with it — leaving a link line that literally starts with `""`.

  * **the build type stays Release.** The top-level `CMakeLists.txt` defines
    `CMAKE_CXX_FLAGS_RELEASE` as `-O2` and defaults to Release when no build
    type is given, so Release is what reproduces `build.sh`. `None` looks
    tidier and silently yields `-O0`, because the project sets flags only for
    Release and Debug.

## Why each dependency is handled the way it is

**Toolchain.** koxtoolchain publishes a prebuilt `kobo.tar.gz` per release, so
there is no toolchain to build. It targets glibc 2.15; the device runs 2.19.

**Lua — headers only.** A loadable module resolves its `lua_*` symbols from the
host interpreter at load time, so linking a Lua library would be wrong and
there is none on the device anyway. `ENABLE_LUA_LINK=OFF` (added for this)
takes the headers without requiring the library. All 37 symbols the wrapper
needs are exported by KOReader's LuaJIT, which is Lua 5.1 ABI-compatible.

**curl — static, linked into the .so.** KOReader ships no libcurl. Kobo
firmware does have one (7.79.1, OpenSSL 1.1), but its version varies by model
and firmware, so depending on it would make the plugin fragile in a way that
only shows up on someone else's device. Static costs about 1 MB and removes the
question. It has to be built `--with-pic`, or the ARM linker refuses the
absolute `R_ARM_THM_MOVW_ABS_NC` relocations when they land in a shared object.

**TLS — LibreSSL, dynamically linked against KOReader's own copy.** KOReader
ships `libssl.so.60` / `libcrypto.so.57` (LibreSSL 4.2.1), so there is no
reason to ship a second TLS stack. Headers come from the matching upstream
tarball and the link target is KOReader's actual binary, so the ABI matches by
construction. `LIBRESSL_VER` and `KOREADER_VER` in `build.sh` must be kept in
step; the build prints the version it found.

Note the link needs `-Wl,--no-as-needed`: the TLS symbols come from inside
`libcurl.a`, which the linker processes *after* `-lssl -lcrypto`, so with
`--as-needed` both get dropped and the module ends up with 118 unresolved
symbols that happen to load anyway. `--no-as-needed` records the `DT_NEEDED`
entries properly.

**CA bundle.** `libcurl` bakes in one path at build time and — unlike the
`curl` command-line tool — ignores `$CURL_CA_BUNDLE`. The compiled-in default
here is KOReader's `data/ca-bundle.crt` at its usual Kobo location, but that is
only a fallback: call `ereol.ApiEnv.setCaBundle(path)` from Lua with the path
actually in use, which is what the plugin does. Leave it unset on a desktop and
the system trust store applies as before.

**nlohmann/json and LuaBridge** are header-only.

## What the result needs at runtime

```
libssl.so.60     libcrypto.so.57     libstdc++.so.6     <- shipped by KOReader
libm.so.6        libgcc_s.so.1       libc.so.6          <- device glibc 2.19
```

Highest versioned symbols required are `GLIBC_2.7`, `GLIBCXX_3.4.32` and
`CXXABI_1.3.15`, against 2.19 / 3.4.33 / 1.3.15 available. `build.sh` prints
these at the end; the Nix build asserts them, and also that `libssl.so.60` and
`libcrypto.so.57` really are in `DT_NEEDED` and that
`luaopen_libereolenwrapper` is exported. A toolchain or KOReader bump that
pushed any of them past what the device has would fail the build rather than
produce a module that only fails at `dlopen` time on the Kobo.

Note CXXABI is at the ceiling exactly, not below it: the margin there is zero,
so a newer C++ runtime in the toolchain is the bump most likely to break this.

## Testing without a device

`qemu-arm` plus the KOReader release's own ARM `luajit` runs the module on the
build machine — enough to catch load failures and to exercise live HTTPS:

```sh
# module loads, and can reach the API over TLS
./cross/kobo/qemu-run.sh cross/kobo/smoke.lua

# ...and the whole login -> loans -> metadata path
EREOL_CARD=<card> EREOL_PIN=<pin> EREOL_LIBRARY=odensebib \
    ./cross/kobo/qemu-run.sh cross/kobo/smoke.lua
```

`qemu-run.sh` also sets `LUA_CPATH` (a C module is found through that, not
through `LD_LIBRARY_PATH`) and passes the release's own `ca-bundle.crt` through
`$EREOL_CA_BUNDLE`, since curl's compiled-in path only exists on a device.

One wrinkle it works around: the toolchain sysroot's glibc 2.15 loader cannot
run the KOReader release binaries — `ld.so` asserts in `elf_dynamic_do_Rel` —
so it hosts the test on a newer ARM glibc instead. That is a qemu-hosting
detail only; the device's real 2.19 loader is fine.
