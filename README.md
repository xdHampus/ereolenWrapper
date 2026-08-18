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

[cross/kobo/README.md](cross/kobo/README.md) explains why each dependency is
handled the way it is.

## License

GPL-3.0 — see [LICENSE](LICENSE).
