{
  description = "yet another quansheng uv-k5 firmware";

  inputs.flake-utils.url = "github:numtide/flake-utils";

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let
          pkgs = nixpkgs.legacyPackages.${system};
        in {
          packages.k5prog = with pkgs; stdenv.mkDerivation {
            pname = "k5prog";
            version = "1.0.0";

            src = fetchFromGitHub {
              owner = "sq5bpf";
              repo = "k5prog";
              rev = "main";
              hash = "sha256-uzhTYCpNjm/I+qlHUF6t9+hGjAvXFlzUM34SAxX5OjE=";
            };

            installPhase = ''
              mkdir -p $out/bin/
              cp k5prog $out/bin/k5prog
            '';
          };
          devShells.default = with pkgs; mkShell {
            nativeBuildInputs = [
              (python312.withPackages (p: with p; [ crcmod ]))
              gnumake gcc-arm-embedded-10
              self.packages.${system}.k5prog
            ];
          };
        }
      );
}
