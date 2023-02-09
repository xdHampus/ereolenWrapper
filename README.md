# eReolen.dk API Wrapper in C++ (with Lua bindings)
This library provides an interface for interacting with eReolen.dk in C++ and Lua.

### Compilation
* `nix build`
* With Lua bindings `nix build .#ereolenWrapperLua`

### Dependencies
+ `nlohmann/json`
+ `cpr`
+ `curl`
+ `openssl`
+ `zlib`
+ With lua `lua5.1` and `luabridge`   
 
### Packages 
+ `ereolenWrapper`: eReolen.dk API Wrapper in C++
+ `ereolenWrapperLua`: eReolen.dk API Wrapper in C++ with Lua bindings
+ `libcpr`: [cpr](https://github.com/libcpr/cpr)
+ `libluabridge`: [luabridge](https://github.com/vinniefalco/LuaBridge)
+ `libgourou`: [libgourou](https://indefero.soutade.fr/p/libgourou)
+ `updfparser`: [updfparser](https://indefero.soutade.fr/p/updfparser)