# E-reader cross-builds

Shared Nix recipes for Kobo and KOReader's `kindlepw2` Kindle compatibility family.
Both targets are available on `x86_64-linux` hosts:

```sh
nix build .#kobo --out-link result-kobo
nix build .#kindlepw2 --out-link result-kindlepw2
```

Each output contains `lib/libereolenwrapper.so`, a Lua C module for KOReader.
The public toolchain-only outputs are `.#koboToolchain` and
`.#kindlepw2Toolchain`.

| Target | Compiler triple | Float ABI | Default KOReader baseline | LibreSSL headers |
|---|---|---|---|---|
| Kobo | `arm-kobo-linux-gnueabihf` | hard | `v2026.03` | `4.2.1` |
| Kindle (`kindlepw2`) | `arm-kindlepw2-linux-gnueabi` | softfp | `v2026.07.1` | `4.3.2` |

The `kindlepw2` build is for the PW2 family running firmware **5.16.2 and below**.
See KOReader's
[installation guide](https://github.com/koreader/koreader/wiki/Installation-on-Kindle-devices).

[default.nix](default.nix) selects each platform's compiler flags, dependency
pins, fallback CA bundle path, and ABI ceilings. [toolchain.nix](toolchain.nix)
packages the prebuilt koxtoolchain compiler for Nix; [toolchain.cmake](toolchain.cmake)
configures CMake using `EREADER_TC`, `EREADER_PREFIX`, `EREADER_TRIPLE`, and
`EREADER_ARCH_FLAGS`.

curl and cpr are compiled statically with PIC. LibreSSL headers match the TLS
libraries extracted from the selected KOReader release. Lua headers are used
without linking a separate Lua runtime. The final module is checked for its ARM
float ABI, TLS dependencies, symbol-version ceilings, and Lua entry point.

## Runtime baseline overrides

The target fixes CPU flags, float ABI, and toolchain. The runtime baseline selects
the KOReader archive supplying the link-time TLS binaries and the matching
LibreSSL headers. The pinned default makes downloads reproducible, not an exact
installed KOReader version requirement. At runtime, the module uses KOReader's
installed libraries; no additional TLS libraries are deployed.

Use the package's `.override` API to select a baseline without changing recipes.
This runnable example explicitly selects the current Kindle default; replace
all four values together for another release:

```sh
nix build --impure --out-link result-kindlepw2 --expr '
	let flake = builtins.getFlake (toString ./.);
	in flake.packages.x86_64-linux.kindlepw2.override {
		runtimeBaseline = {
			koreaderVersion = "v2026.07.1";
			koreaderHash = "sha256-6h9XXFRJKixnnRKLfzIQ/X1qh+X1of8fen/iCA/2j4Y=";
			libresslVersion = "4.3.2";
			libresslHash = "sha256-7fAa7iTGXWnmqe/LnUS82mgv+dTzu72V55Th36kIR7U=";
		};
	}'
```

The same API works on `.kobo`. `koreaderHash` hashes the upstream
`koreader-<target>-<version>.zip`; `libresslHash` hashes the matching upstream
LibreSSL tarball. Obtain each hash with `nix store prefetch-file --json <url>`.
Find the defaults in [default.nix](default.nix) and [libressl-sdk.nix](libressl-sdk.nix).
Partial baselines are rejected so versions and hashes must be supplied together.

Overrides do not change target ABI ceilings or expected TLS library names
(`libssl.so.60` and `libcrypto.so.57`). A release that changes those names needs
recipe changes. Identical names alone do not guarantee symbol compatibility;
check the installed TLS, C++ runtime, and Lua ABI before choosing a baseline.
The newest release may require symbols unavailable in an older installation.
Nix intentionally fetches fixed versions and hashes, not a moving "latest" URL.

The standalone build and QEMU smoke-test scripts remain Kobo-only under
[../kobo/](../kobo/README.md), including their ignored `work/` directory.
See the top-level [Kindle instructions](../../README.md#kindle-cross-build)
for Kindle deployment and runtime compatibility details.