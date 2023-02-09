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
        ereolenWrapperDrv = pkgs.callPackage ./default.nix { cpr = libcprDrv; libgourou = libgourouDrv; };

        ereolenWrapperLuaDrv = pkgs.callPackage ./default.nix {
          cpr = libcprDrv; libgourou = libgourouDrv;
          enableLua = true;
          lua = pkgs.lua5_1;
          luabridge = libluabridgeDrv;
        };

        libcprDrv = pkgs.callPackage ./libs/cpr/default.nix { };
        libluabridgeDrv = pkgs.callPackage ./libs/luabridge/default.nix { };
        updfparserDrv = pkgs.callPackage ./libs/updfparser/default.nix { };
        libgourouDrv = pkgs.callPackage ./libs/libgourou/default.nix { updfparser = updfparserDrv; };

        pkgs = import nixpkgs { inherit system; };
        pkgsUnstable = import nixpkgs-master { inherit system; };
        pkgsUnfree = import nixpkgs-master {
          inherit system;
          config.allowUnfree = true;
        };
      in {
        devShell = pkgs.mkShell rec {
          name = "ereolenWrapper";
          packages = with pkgs; [
            # Development Tools
            gitFull
            gdb
            pkgsUnstable.cppcheck
            #pkgsUnfree.vscode-extensions.ms-vscode.cmake-tools
            pkgsUnfree.vscode-extensions.ms-vscode.cpptools
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
          libgourou = libgourouDrv;
          updfparser = updfparserDrv;
        };
        checks = { 
          tests = pkgs.callPackage ./default.nix {
            cpr = libcprDrv; libgourou = libgourouDrv;
            enableTests = true;
          };
          testsLua =  pkgs.callPackage ./default.nix {
            cpr = libcprDrv; libgourou = libgourouDrv;
            enableLua = true;
            lua = pkgs.lua5_1;
            luabridge = libluabridgeDrv;
            enableTests = true;
          };
        };
      });
}
