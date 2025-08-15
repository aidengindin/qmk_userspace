{
  description = "QMK development environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          buildInputs = with pkgs; [
            qmk
            python3
            avrdude
            dfu-util
            teensy-loader-cli
          ];

          shellHook = ''
            echo "QMK development environment loaded"
            echo "Run 'qmk setup' to initialize QMK if this is your first time"
          '';
        };
      });
}