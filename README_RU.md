<img width="1220" height="677" alt="Без названия247_20261005113508" src="https://github.com/user-attachments/assets/f830497f-a618-4114-a20b-4a9deaeb7d68" />



# Форк Hatsune Miku Desktop Mascot на hyprland


> *Та самая Мику из тренда «слышь ты залип, опа опа оп»!*
> 
> [Read in English](README.md)
> ---
## Русская версия

Маскот для рабочего стола Linux систем, написанный на C с использованием библиотеки Raylib. Wallpaper Engine или Anima Engine не требуется.

### Совместимость

 * Форк 100% работает на: Hyprland и KDE Plasma
 
### Зависимости

* Для Arch-подобных дистрибутивов:
```bash
sudo pacman -S gcc raylib libx11
```

* Для Debian/Ubuntu-подобных дистрибутивов:
```bash
sudo apt update
```
```bash
sudo apt install build-essential libraylib-dev libx11-dev libxext-dev

```

* Для Fedora-подобных дистрибутивов:
```bash
  sudo dnf install gcc make raylib-devel libX11-devel libXext-devel
  ```

### Сборка и запуск

  * Клонируйте репозиторий и перейдите в папку:
```bash
  git clone https://github.com/b42h4n/miku4hypr
   ```
```bash
   cd miku4hypr
   ```
  * Скомпилируйте:
```bash
   gcc main.c -o miku -lraylib -lX11 -lXext -lGL -lm -lpthread -ldl -lrt -lXext
   ```
  * Так же, пропишите в .config/hypr/config/windowrules.lua следующее:
```bash
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

  * Запустите маскота:
```bash
   ./miku
   ```


### Примечание

 * На Мику не работают клики. Чтобы её закрыть, выполните в терминале:
```bash
  pkill -9 -i miku
  ```
