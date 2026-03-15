{pkgs ? import <nixpkgs> {}}:
pkgs.mkShell {
  packages = with pkgs; [
    gcc
    gnumake
    pkg-config

    xorg.libX11.dev
    xorg.libXft.dev
    xorg.libXinerama.dev

    xorg.xinit
    xorg.xsetroot
  ];
}
