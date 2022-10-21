{
  description = "C++ Wrapper for eReolen.dk RPC API";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    nixpkgs-master.url = "github:NixOS/nixpkgs/master";
    utils.url = "github:numtide/flake-utils";
    utils.inputs.nixpkgs.follows = "nixpkgs";
  };

  outputs = { self, nixpkgs, nixpkgs-master, utils, ... }@inputs:
    utils.lib.eachDefaultSystem (system:
      let
        ereolenWrapperDrv = pkgs.callPackage ./default.nix { cpr = libcprDrv; };
        ereolenWrapperLuaDrv = pkgs.callPackage ./default.nix {
          cpr = libcprDrv;
          enableLua = true;
          lua = pkgs.lua5_1;
          luabridge = libluabridgeDrv;
        };

        testsDrv = pkgs.callPackage ./default.nix {
          cpr = libcprDrv;
          enableTests = true;
        };

        libcprDrv = pkgs.callPackage ./libs/cpr/default.nix { };
        libluabridgeDrv = pkgs.callPackage ./libs/luabridge/default.nix { };
        pkgs = import nixpkgs { inherit system; };
        pkgsUnstable = import nixpkgs-master { inherit system; };
      in {
        devShell = pkgs.mkShell rec {
          name = "ereolenWrapper";
          packages = with pkgs; [
            # Development Tools
            gitFull
            gdb
            pkgsUnstable.cppcheck
            # Dependencies
            llvmPackages_11.clang
            cmake
            zlib
            openssl
            gtest
            nlohmann_json
            curl
            python39
            python39Packages.flask
          ];
        };

        defaultPackage = ereolenWrapperDrv;
        packages = {
          ereolenWrapper = ereolenWrapperDrv;
          ereolenWrapperLua = ereolenWrapperLuaDrv;
          libcpr = libcprDrv;
          libluabridge = libluabridgeDrv;
        };
        checks = { tests = testsDrv; };
      });
}
