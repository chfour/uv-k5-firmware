{
  description = "yet another quansheng uv-k5 firmware";

  inputs.flake-utils.url = "github:numtide/flake-utils";

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
        in {
          devShells.default = with pkgs; mkShell {
            nativeBuildInputs = [
              (python312.withPackages (p: with p; [ crcmod ]))
              gnumake gcc-arm-embedded-10
            ];
          };
        }
      );
}
