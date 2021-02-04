
Debian
====================
This directory contains files used to package bitcoinoild/bitcoinoil-qt
for Debian-based Linux systems. If you compile bitcoinoild/bitcoinoil-qt yourself, there are some useful files here.

## bitcoinoil: URI support ##


bitcoinoil-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bitcoinoil-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bitcoinoil-qt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoinoil128.png` to `/usr/share/pixmaps`

bitcoinoil-qt.protocol (KDE)

