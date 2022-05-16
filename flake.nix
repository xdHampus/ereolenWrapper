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
    ];
    ereolenWrapperDrv = pkgs.callPackage ./default.nix {customLibs=clibs;};
    libcprDrv = pkgs.callPackage ./libs/cpr/default.nix {};
    libunityDrv = pkgs.callPackage ./libs/unity/default.nix {};
    testsDrv = pkgs.callPackage ./tests.nix {customLibs=clibs;};
    ctestsDrv = pkgs.callPackage ./src/test/c-interface/tests.nix {
      customLibs=[
        ereolenWrapperDrv
        (pkgs.callPackage ./libs/unity/default.nix {unityExtensionFixture = true;})
      ];
    };
    pkgs = import nixpkgs {
      inherit system;
      overlays = [];
      config.allowUnfree = true;
    };
  in {
    devShell = pkgs.mkShell rec {
      name = "ereolenWrapper";
      packages = with pkgs; [
        # Development Tools
        gitFull #jetbrains.clion
        # Dependencies
        llvmPackages_11.clang cmake zlib openssl gtest # cmake FetchContent #cmakeCurses
        nlohmann_json curl
        python39 python39Packages.flask 
      ] ++ clibs;
    };
    packages = {
      ereolenWrapper = ereolenWrapperDrv;
      libcpr = libcprDrv;
      libunity = libunityDrv;
    }; 
    defaultPackage = ereolenWrapperDrv;
    checks = {
      tests = testsDrv;
      ctests = ctestsDrv;
    };
  });
}
