# Coucou

Use remote linux server with ssh on vscode, SSHing Over WiFi. Or use httpd .service 
change the .profil to launch script at the login.
Create different users
Mounting a Local Drive

(server versions, or minimal. Although Minimal installs will usually not come with some of the programs you might expect.

Another option you have would be to switch to a text terminal on your existing Linux install. CTRL+ALT+F1 will switch you to the first text terminal, CTRL+ALT+F2 to the second, etc.

You can also change your current install to only boot to init 3, which would prevent a desktop manager from running in most Linux distros.)

Use ftdi to flash on card
use uart to communicate with card
have several card on Ls /dev/ttyusb0 or 1 or 2 or with rj45 (like raspberry)
use big back up drives
use vlan etc
add sensors to my house, control light, music
(Network switch, ups, power strip, )
Yes, you can start your home server remotely using software like a Baseboard Management Controller (BMC). KVM to powerup

## OS
Use arch os (with exemple endeavouros distro if you don't want hard mode)
- use own units .service in systemd

## packages

- use Vim for text editing

- use terminal to google etc, show internet pages on the terminal

- spotify terminal

## Linux commands
- tree # To see how the files are disposed
- Locate

### Performance monitoring

- htop # monitor things on your pc
- iftop # To see network trafics
- iotop # To see discs trafics (df -h: Shows disk space for all filesystems in easy-to-read formats (GB, MB).)
- Btop # looks cool

## Desktop
Switch to a virtual console: Ctrl+Alt+F2 (or F3, F4…) to change betwen the x terminals
(To exit switch to a virtual console then write killall Xorg)
### dwm
#### Install
https://www.youtube.com/watch?v=jD8BtmMK0do
Dependences

sudo pacman -S base-devel git xorg-server xorg-xinit libx11 libxft libxinerama xterm dmenu libxrandr libxinerama picom feh xorg-xrandr 
sudo pacman -S xorg-apps

to launch dwm with st terminal (or kitty, Allacritty,...), change the terminal in the config.h that is at ~/dwm/config.h or ~/st-btw/config.h

Clone the dwm repo, sudo make clean install

have to change xserver .xinit file that is at ~/.xinit. add what you want to launch at start (when typing startx). add "exec dmw" at the end.



#### Configure it
Setting wallpaper:
1. Install feh
$ sudo pacman -S feh
2. Set wallpaper
$ feh --bg-scale foobar.jpg
3. put it in the .xinit to execute at startx launch


Fonts:
1. download a Nerd font (https://www.nerdfonts.com/font-downloads)
2. unzip, leave in a directory, move to ~/.local/share/font
3. change the dwm config.h file, mettre le nom du dossier.
4. compile dwm

dwmBlocks(time, battery, keyboard language, temperature, etc.....):
1.

compositioning, Transparent windows + blur & nice effects (doesn't work):
1. Install compositioning stuff
$ sudo pacman -S picom
2. Run xcompmgr (and add to your .xinitrc):
$ xcompmgr &
3. Chose transparency (this example is 50% transparency)
$ transset .50
4. Click the window you want to be transparent

(- Desktop environnement : KDE plasma)
(- use hyprland, etc)
(- remote desktop : krdc)

## Mail
- Use aerc to email with the terminal
- install the pager less (important to use it for aerc etc.)

## All the configuration files location
 - for xserver, .xinit is at ~/.xinit
 - for dwm, config.h is at ~/dwm/config.h or ~/st-btw/config.h
 - for the rest, ~/.config/...... 



(See more, 
fish shell, NerdFonts, FiraCode Nerd Fonts, jetbrains Mono (font), i3, kitty (terminal), dunst, feh, lxappearance, flameshot, rose-pine-gtk, picom, nnn (file manager), redshift )
