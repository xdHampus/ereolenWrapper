{
  description = "C++ Wrapper for eReolen.dk RPC API";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils, ... }@inputs:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };

        # cpr comes from nixpkgs; the vendored 1.10.0 no longer compiles
        # against curl 8. libgourou and updfparser are gone entirely: ACSM
        # fulfilment happens in acsm.koplugin, in Lua, on the KOReader side.
        libluabridgeDrv = pkgs.callPackage ./libs/luabridge/default.nix { };

        ereolenWrapperDrv = pkgs.callPackage ./default.nix { };

        ereolenWrapperLuaDrv = pkgs.callPackage ./default.nix {
          enableLua = true;
          lua = pkgs.lua5_1;
          luabridge = libluabridgeDrv;
        };
      in {
        devShells.default = pkgs.mkShell rec {
          name = "ereolenWrapper";
          packages = with pkgs; [
            # Development Tools
            gitFull
            gdb
            cppcheck
            # Dependencies
            cmake
            zlib
            openssl
            gtest
            nlohmann_json
            curl
            # Needs to be a withPackages env: a bare python3 + python3Packages.flask
            # does not put flask on the interpreter's import path.
            (python3.withPackages (ps: with ps; [ flask ]))
          ];
        };

        packages = {
          default = ereolenWrapperDrv;
          ereolenWrapper = ereolenWrapperDrv;
          ereolenWrapperLua = ereolenWrapperLuaDrv;
          libluabridge = libluabridgeDrv;
          libcpr = pkgs.cpr;
        };
        checks = {
          tests = pkgs.callPackage ./default.nix {
            enableTests = true;
          };
          testsLua = pkgs.callPackage ./default.nix {
            enableLua = true;
            lua = pkgs.lua5_1;
            luabridge = libluabridgeDrv;
            enableTests = true;
          };
        };
      });
}
