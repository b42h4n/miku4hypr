<img width="1220" height="677" alt="Без названия247_20261005113508" src="https://github.com/user-attachments/assets/d4a60f81-9a78-4d10-873d-0384aa64311a" />



# Fork Hatsune Miku Desktop Mascot for hyprland


> Miku from tiktok trend
> 
> [RU ver](README_RU.md)

---

## English Version


Desktop mascot for Linux systems written in pure C using Raylib. No Wallpaper Engine or Anima Engine required.


### Compatibility

* Fork 100% Working on: Hyprland, and KDE Plasma


### Dependencies


* For Arch-based distros:
```shell
sudo pacman -S gcc make raylib libx11
```

* For Debian/Ubuntu-based distros:
```shell
sudo apt update
```
```shell

sudo apt install build-essential libraylib-dev libx11-dev libxext-dev
```

* For Fedora-based distros:
```shell
  sudo dnf install gcc make raylib-devel libX11-devel libXext-devel
  ```


### Building and Running

 * Clone the repository and enter the directory:
   
```shell
 git clone https://github.com/b42h4n/miku4hypr
 ```
```shell
 cd miku4hypr
  ```

 * Compile
```shell
   gcc main.c -o miku -lraylib -lX11 -lGL -lm -lpthread -ldl -lrt -lXext
   ```
 * Run the mascot:
```shell
   ./miku
  ```
 * Also, you need add this on ~/.config/hypr/hyprland.lua (or ~/.config/hypr/config/windowrules.lua if you do modular partitioning):
```lua
  hl.window_rule({
    match = { title = "^(Hatsune Miku)$" },
    float = true,
    border_size = 0,
    no_shadow = true,
    no_blur = true,
    pin = true,
    no_initial_focus = true,
    opacity = "1.0 1.0 override",
    no_focus = true,
    move = { 1120, 433 },
  })
  ```
If your hyprland version is 0.52 or lower, add this to ~/.config/hypr/hyprland.conf:
```hyprland
windowrulev2 = float,    title:^(Hatsune Miku)$
windowrulev2 = pin,      title:^(Hatsune Miku)$
windowrulev2 = move 100%-w 433, title:^(Hatsune Miku)$
windowrulev2 = nofocus,  title:^(Hatsune Miku)$
windowrulev2 = noborder, title:^(Hatsune Miku)$
windowrulev2 = noshadow, title:^(Hatsune Miku)$
windowrulev2 = noanim,   title:^(Hatsune Miku)$
windowrulev2 = rounding 0, title:^(Hatsune Miku)$
```
And if your hyprland version is 0.53, add this:
```hyprlang
windowrule = float on, match:title ^(Hatsune Miku)$
windowrule = pin on, match:title ^(Hatsune Miku)$
windowrule = move (monitor_w-window_w) 433, match:title ^(Hatsune Miku)$
windowrule = no_focus on, match:title ^(Hatsune Miku)$
windowrule = no_border on, match:title ^(Hatsune Miku)$
windowrule = no_shadow on, match:title ^(Hatsune Miku)$
windowrule = no_anim on, match:title ^(Hatsune Miku)$
windowrule = rounding 0, match:title ^(Hatsune Miku)$
```

### Note

* Direct clicks on Miku are disabled. To close the mascot, run:
```bash
  pkill -9 -i miku
  ```
