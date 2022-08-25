{
  description = "C++ Wrapper for eReolen.dk RPC API";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/master";
    utils.url = "github:numtide/flake-utils";
    utils.inputs.nixpkgs.follows = "nixpkgs";
  };

  outputs = { self, nixpkgs, ... }@inputs: inputs.utils.lib.eachSystem [
    "x86_64-linux" "i686-linux" "aarch64-linux" "x86_64-darwin"
  ] (system: 
  let 
    clibs = [
      (pkgs.callPackage ./libs/cpr/default.nix {})
      (pkgs.callPackage ./libs/luabridge/default.nix {})
    ];
    ereolenWrapperDrv = pkgs.callPackage ./default.nix {customLibs=clibs;};
    testsDrv = pkgs.callPackage ./tests.nix {customLibs=clibs;};

    libcprDrv = pkgs.callPackage ./libs/cpr/default.nix {};
    libunityDrv = pkgs.callPackage ./libs/unity/default.nix {};
    libluabridgeDrv = pkgs.callPackage ./libs/luabridge/default.nix {};

    ctestsDrv = pkgs.callPackage ./src/test/c-interface/tests.nix {
      customLibs=[
        ereolenWrapperDrv
        (pkgs.callPackage ./libs/unity/default.nix {unityExtensionFixture = true;})
      ];
    };
    pkgs = import nixpkgs { inherit system; overlays = []; config.allowUnfree = true; };
  in {
    devShell = pkgs.mkShell rec {
      name = "ereolenWrapper";
      packages = with pkgs; [
        # Development Tools
        gitFull gdb valgrind
        jetbrains.clion
        # Dependencies
        llvmPackages_11.clang cmake zlib openssl gtest # cmake FetchContent #cmakeCurses
        nlohmann_json curl
        python39 python39Packages.flask 
      ] ++ clibs;
    };

    defaultPackage = ereolenWrapperDrv;
    packages = {
      ereolenWrapper = ereolenWrapperDrv;
      libcpr = libcprDrv;
      libunity = libunityDrv;
      libluabridge = libluabridgeDrv;
    };
    checks = {
      tests = testsDrv;
      ctests = ctestsDrv;
    };
  });
}
