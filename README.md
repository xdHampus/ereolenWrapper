# ereolenWrapper

A C++20 client for the JSON-RPC API behind [eReolen.dk](https://ereolen.dk), the
Danish public libraries' e-book service. Optionally builds as a Lua 5.1 module,
which is how [ereolen.koplugin](https://github.com/xdHampus/ereolen.koplugin)
uses it inside KOReader.

There is no public documentation for this API; the surface here was recovered
from the official app.

## What it covers

| | |
|---|---|
| `Auth` | authenticate, deauthenticate, isAuthenticated |
| `Item` | search, suggestions, records, covers, reviews, related titles, loan status, createLoan, download |
| `Profile` | loans, reservations, loan history, want-to-read list, and the calls that mutate them |
| `ApiEnv` | endpoint, app version, language, the library list, CA bundle |

Every call returns a `Response<T>` carrying `success`, `code`, `message` and
`data`, so a rejection from the server arrives as a value rather than an
exception.

## Using it from Lua

```lua
require("libereolenwrapper")   -- registers the global `ereol` table

local library = ereol.ApiEnv.getLibraryFromCode("odensebib")
local auth = ereol.Auth.authenticate(card, pin, library)
assert(auth.success, auth.message)

local settings = ereol.QuerySettings()
settings.startIndex = 0
settings.endIndex = 5          -- a count, capped at 200 — not an end offset

local page = ereol.Item.search("Tove Ditlevsen", auth.data, settings)
assert(page.success, page.message)

print(page.data.count .. " hits")
-- Results arrive grouped: one collection per title, holding its editions.
for _, collection in ipairs(page.data.data) do
    print("  " .. collection[1].title)
end

ereol.Auth.deauthenticate(auth.data)
```

```
107 hits
  Tove Ditlevsen om sig selv
  Tove Ditlevsen : myte og liv
  Tove Ditlevsen : et portræt
  Ditlevsen : en biografi
  Kærlig hilsen, Tove : breve til en forlægger
```

## Building

```sh
nix build                      # the C++ library
nix build .#ereolenWrapperLua  # ...with the Lua module
nix build .#kobo               # ...cross-compiled for a Kobo e-reader
nix build .#kindlepw2          # ...for KOReader's kindlepw2 Kindle family
```

Or with CMake directly — needs `nlohmann_json`, `cpr`, `curl`, `openssl` and
`zlib`, plus `lua5.1` and [LuaBridge](https://github.com/vinniefalco/LuaBridge)
for the Lua build:

```sh
cmake -S . -B build -DENABLE_LUA=ON && cmake --build build
```

`nix develop` gives you all of that and the mock server's Python environment.

## Tests

The suite runs against a Flask mock of the API, so it needs no card and no
network:

```sh
nix develop -c flask run --host=0.0.0.0 &   # FLASK_APP=src/test/mock-server/app.py
nix run .#checks.x86_64-linux.tests
nix run .#checks.x86_64-linux.testsLua
```

The mock reads `TEST_API_KEY`, `TEST_LIBRARY`, `TEST_USERNAME` and
`TEST_PASSWORD` and answers as that user; the tests read the same four, so both
sides have to agree.

## Kobo cross-build

`nix build .#kobo` produces an ARM `libereolenwrapper.so` that KOReader's LuaJIT
can load on a Kobo, built with koreader/koxtoolchain against the device's
glibc 2.19 and linked to the LibreSSL that KOReader itself ships. The build
asserts its own ABI ceiling, so a toolchain bump that outgrew the device fails
here rather than at `dlopen` time on the e-reader.

[cross/ereader/README.md](cross/ereader/README.md) describes the shared recipes;
[cross/kobo/README.md](cross/kobo/README.md) explains the Kobo-specific dependency
choices and standalone scripts.

## Kindle cross-build

On an `x86_64-linux` host:

```sh
nix build .#kindlepw2 --out-link result-kindlepw2
```

This produces `result-kindlepw2/lib/libereolenwrapper.so` for the **PW2 family**
running firmware **5.16.2 and below**. See the
[official KOReader installation guide](https://github.com/koreader/koreader/wiki/Installation-on-Kindle-devices).

The `kindlepw2` target determines the CPU flags, float ABI, and toolchain.
It uses koxtoolchain 2025.05's
`arm-kindlepw2-linux-gnueabi` compiler and the soft-float calling convention;
the Kobo hard-float binary is not interchangeable with it. Both cross targets
are available only on `x86_64-linux` hosts.

The default runtime baseline is **`koreader-kindlepw2-v2026.07.1`**, with matching
LibreSSL 4.3.2 headers. This pins reproducible link-time dependencies; it is
not an exact installed KOReader version requirement. Other releases can work
if their TLS libraries, C++ runtime, and Lua ABI are compatible.

Copy the module into `/mnt/us/koreader/plugins/ereolen.koplugin/` on the Kindle.
It resolves Lua symbols from KOReader's LuaJIT and uses KOReader's bundled
`libssl.so.60`, `libcrypto.so.57` (LibreSSL 4.3.2), and `libstdc++.so.6`.
curl and cpr are compiled for the `kindlepw2` target and linked statically into the module.
The fallback CA bundle is `/mnt/us/koreader/data/ca-bundle.crt`; the plugin can
override it with `ereol.ApiEnv.setCaBundle(path)` for other installation paths.

The recipes are shared with Kobo under `cross/ereader/`. Callers can select
another KOReader archive and matching LibreSSL headers using the
[runtimeBaseline override](cross/ereader/README.md#runtime-baseline-overrides),
without editing the shared recipes. When changing baselines, check the TLS
dependencies and runtime ABI limits together; linking against the latest release
does not guarantee compatibility with older installed releases.
The build checks ARM soft-float ABI, TLS dependencies, the Lua entry point,
and symbol requirements against glibc 2.12.2, GLIBCXX 3.4.33, and CXXABI 1.3.15.
The glibc limit is the toolchain baseline, not a claim about every firmware's
installed version. Loading and making an HTTPS request on the device remain
the final runtime checks.

`nix build .#kindlepw2Toolchain` builds just the cross-compiler.

### Cross-build layout

```text
cross/
  ereader/  # shared Nix recipes and toolchain.cmake for Kobo and Kindle kindlepw2
  kobo/     # Kobo-only build.sh, qemu-run.sh, smoke.lua, and scratch work/
```

## License

GPL-3.0 — see [LICENSE](LICENSE).
