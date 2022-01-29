{
  description = "C++ Wrapper for eReolen.dk RPC API";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/master";
    utils.url = "github:numtide/flake-utils";
    utils.inputs.nixpkgs.follows = "nixpkgs";
  };

  outputs = { self, nixpkgs, ... }@inputs: inputs.utils.lib.eachSystem [
    "x86_64-linux" "i686-linux" "aarch64-linux" "x86_64-darwin"
  ] (system: let pkgs = import nixpkgs {
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

                   # Development time dependencies
                   gtest

                   # Build time and Run time dependencies
                   nlohmann_json
                   
                 ];
               };

               defaultPackage = pkgs.callPackage ./default.nix {};
             });
}
