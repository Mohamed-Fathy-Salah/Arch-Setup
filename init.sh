#!/bin/sh
sudo pacman -Syu zsh
chsh -s $(which zsh)

# install xcompmgr if u want opacity in terminal
sudo pacman -Syu base-devel libX11-devel libXft-devel libXinerama-devel freetype-devel fontconfig-devel gvim xorg lf sxiv dmenu htop maim w3m python3 ueberzug ffmpeg chafa exiftool ImageMagick xclip xdotool pulseaudio vscode pamixer ncmpcpp calcurse pcmanfm gvfs kdeconnect git curl wget xournalpp mpv xwallpaper gromit-mpxpoppler libreoffice numlockx

#mkdir ~/apps ; cd ~/apps
#git clone git@github.com:Mohamed-Fathy-Salah/Arch-Setup.git

cd ~/apps/Arch-Setup/dwm ; sudo make clean install
cd ~/apps/Arch-Setup/st  ; sudo make clean install
cd ~/apps/Arch-Setup/dwmblocks-async  ; sudo make clean install
cd ~/apps/Arch-Setup/dmenu ; sudo make clean install

#cd ~/apps
#git clone https://github.com/Naheel-Azawy/stpv.git
#cd stpv ; sudo make install
cd ~/apps/stpv ; sudo make install
