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

    pkgs = import nixpkgs {
      inherit system;
      overlays = [];
      config.allowUnfree = true;
    };
  in {
    devShell = pkgs.mkShell rec {
      # Update the name to something that suites your project.
      name = "ereolenWrapper";

      packages = with pkgs; [
      # Development Tools
      llvmPackages_11.clang
      cmake
      cmakeCurses
      gitFull # cmake FetchContent
      #jetbrains.clion

      # Development time dependencies
      gtest
      python39
      python39Packages.flask

      # Build time and Run time dependencies
      nlohmann_json
      openssl
      curl
      zlib
      ] ++ clibs;

    };
    packages = {
      ereolenWrapper = pkgs.callPackage ./default.nix {customLibs=clibs;};
      libCpr = pkgs.callPackage ./libs/cpr/default.nix {};
      libUnitytest = pkgs.callPackage ./libs/unity/default.nix {};
      tests = pkgs.callPackage ./tests.nix {customLibs=clibs;};
      cTests = pkgs.callPackage ./src/test/c-interface/tests.nix {
        customLibs=[
          #(pkgs.callPackage ./default.nix {customLibs=clibs;})
          (pkgs.callPackage ./libs/unity/default.nix {unityExtensionFixture = true;})
        ];
      };
    }; 
    defaultPackage = pkgs.callPackage ./default.nix {customLibs=clibs;};
    checks = {
      tests = pkgs.callPackage ./tests.nix {customLibs=clibs;};
      cTests = pkgs.callPackage ./src/test/c-interface/tests.nix {
        customLibs=[
          #(pkgs.callPackage ./default.nix {customLibs=clibs;})
          (pkgs.callPackage ./libs/unity/default.nix {unityExtensionFixture = true;})
        ];
      };
    };
  });
}
