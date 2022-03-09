#!/bin/sh
sudo pacman -Syu zsh
chsh -s $(which zsh)

# install xcompmgr if u want opacity in terminal
sudo pacman -Syu base-devel libX11-devel libXft-devel libXinerama-devel freetype-devel fontconfig-devel gvim xorg lf sxiv dmenu htop maim w3m python3 ueberzug ffmpeg chafa exiftool ImageMagick xclip xdotool pulseaudio vscode pamixer ncmpcpp calcurse pcmanfm gvfs kdeconnect git curl wget xournalpp mpv xwallpaper gromit-mpxpoppler libreoffice

cd ~/apps/suckless/dwm ; sudo make clean install
cd ~/apps/suckless/st  ; sudo make clean install
cd ~/apps/suckless/dwmblocks-async  ; sudo make clean install
cd ~/apps/suckless/dmenu ; sudo make clean install
cd ~/apps/suckless/stpv ; sudo make install
