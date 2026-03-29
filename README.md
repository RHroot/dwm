# ⚡ dwm - Dynamic Window Manager

> A blazingly fast, minimal, and extensible window manager for X11 with a modern customized build

![dwm version](https://img.shields.io/badge/dwm-v6.8-blue?style=flat-square)
![license](https://img.shields.io/badge/license-MIT-green?style=flat-square)
![C](https://img.shields.io/badge/language-C-00599C?style=flat-square)

---

## ✨ Features

### 🎯 Core Features
- **⚡ Lightning Fast** - Written in C with minimal overhead
- **🎨 Highly Customizable** - Modify behavior by editing source code (no configuration files)
- **🏷️ Dynamic Tagging** - Flexible workspace management with tag-based window organization
- **🔄 Tiling Layouts** - Master/stack tiling by default, with extensible layout options
- **🖥️ Multi-Monitor Support** - Full Xinerama support for multi-head setups
- **📦 Minimal Dependencies** - Only X11 libraries required

### 🚀 Advanced Patches & Features
This build includes several quality-of-life enhancements:

- **🖼️ Actual Fullscreen** - True fullscreen mode support
- **⏭️ Adjacent Tag Navigation** - Skip vacant tags for efficient workspace switching
- **🔄 Restart Signal** - Reload configuration without restarting X
- **💾 Preserve on Restart** - Window state persists after config reload
- **🚀 Cool Autostart** - Automatic daemon and application launching

### 🎯 Integrated Components
- **📊 slstatus** - Lightweight status bar for displaying system information
- **🎨 Custom Color Scheme** - Modern dark theme with accent colors
- **🔤 Nerd Font Support** - Beautiful icons and glyphs via FiraCode Nerd Font

---

## 📋 Requirements

Before building, ensure you have the following dependencies installed:

```bash
# Debian/Ubuntu
sudo apt-get install build-essential libx11-dev libxft-dev libxinerama-dev

# Arch/Manjaro
sudo pacman -S base-devel libx11 libxft libxinerama

# Fedora
sudo dnf install gcc make libX11-devel libXft-devel libXinerama-devel

# NixOS
nix-shell  # Uses the provided shell.nix
```

### Optional Dependencies (for enhanced functionality)
- `picom` - Compositing manager with transparency and effects
- `dunst` - Lightweight notification daemon
- `rofi` - Application launcher
- `slstatus` - Status bar (included in this repo)
- `clipmenu` - Clipboard manager
- `feh` - Wallpaper setter
- `nm-applet` - Network manager applet

---

## 🔨 Installation & Building

### Quick Start

```bash
# Clone/navigate to the dwm directory
cd ~/dwm

# Build and install to ~/.local/bin
make clean install

# Or use sudo for system-wide installation
sudo make clean install
```

### Advanced Configuration

Edit `config.mk` to customize installation paths:

```makefile
PREFIX = ${HOME}/.local          # Installation directory
MANPREFIX = ${PREFIX}/share/man  # Manual page directory
```

---

## 🚀 Running dwm

### Using startx

Add this to your `~/.xinitrc`:

```bash
# Start required daemons
pgrep -x picom >/dev/null || picom &
pgrep -x dunst >/dev/null || dunst &

# Start dwm
exec dwm
```

### Using a Display Manager (GDM, LightDM, etc.)

Create `/usr/share/xsessions/dwm.desktop`:

```ini
[Desktop Entry]
Name=dwm
Comment=Dynamic Window Manager
Exec=dwm
Type=Application
```

### Display-Specific Launch

```bash
DISPLAY=:1 dwm
```

### With Status Bar Information

Use the included `slstatus` to display system information:

```bash
slstatus &
exec dwm
```

---

## ⌨️ Keybindings

### Window Management
| Binding | Action |
|---------|--------|
| `Mod + Return` | Open terminal |
| `Mod + Space` | Application launcher (rofi) |
| `Mod + Shift + Space` | Alternative launcher |
| `Mod + Q` | Close focused window |
| `Mod + F` | Toggle fullscreen |
| `Mod + B` | Toggle statusbar |

### Workspace Navigation
| Binding | Action |
|---------|--------|
| `Mod + J` | View previous tag |
| `Mod + K` | View next tag |
| `Mod + Shift + Left` | Move window to previous tag |
| `Mod + Shift + Right` | Move window to next tag |
| `Alt + J` | Focus next window |
| `Alt + K` | Focus previous window |

### Application Shortcuts
| Binding | Action |
|---------|--------|
| `Mod + B` | Open personal browser |
| `Mod + Shift + B` | Open work browser |
| `Mod + V` | Clipboard manager |
| `Mod + Shift + V` | Volume control (pavucontrol) |

### Layout Management
| Binding | Action |
|---------|--------|
| `Mod + I` | Increase master windows |
| `Mod + D` | Decrease master windows |
| `Mod + H/L` | Adjust master area width |

> **Note:** `Mod` key = Alt (configurable in config.h)

---

## 🎨 Customization

### Changing the Color Scheme

Edit `config_colors.h`:

```c
static const char col_bg[]     = "#121316";  // Background
static const char col_bg_alt[] = "#1e2022";  // Alt background
static const char col_bg_sel[] = "#292a2c";  // Selection background
static const char col_fg[]     = "#e3e2e5";  // Foreground
static const char col_fg_dim[] = "#c3c6cf";  // Dimmed foreground
static const char col_accent[] = "#adc8f0";  // Accent color
```

### Changing the Font

Edit `config.h` and modify the fonts array:

```c
static const char *fonts[] = {"FiraCode Nerd Font:size=14", "monospace:size=12"};
```

### Custom Keybindings

Edit the `keys[]` array in `config.h` and recompile:

```c
static const Key keys[] = {
    {MODKEY, XK_Return, spawn, {.v = myterminal}},
    // Add your custom bindings here
};
```

### Autostart Programs

Edit the `autostart[]` array in `config.h`. Programs listed here will start automatically:

```c
static const char *const autostart[] = {
    "picom", NULL,        // Compositor
    "dunst", NULL,        // Notification daemon
    "slstatus", NULL,     // Status bar
    // Add more here
    NULL
};
```

### Window Rules

Define behavior for specific applications in the `rules[]` array:

```c
static const Rule rules[] = {
    {"Firefox",     NULL, NULL, 1 << 0,  0, -1},  // Firefox on tag 1
    {"Gimp",        NULL, NULL, 0,       1, -1},  // Gimp floats
    {"qemu-system", NULL, NULL, 1 << 2,  1, -1},  // QEMU floats on tag 3
};
```

---

## 📁 Project Structure

```
dwm/
├── dwm.c              # Main window manager source
├── drw.c/drw.h        # Drawing/font rendering library
├── util.c/util.h      # Utility functions
├── config.h           # Current configuration (generated from config.def.h)
├── config.def.h       # Default configuration template
├── config.mk          # Build configuration
├── config_colors.h    # Color scheme definition
├── slstatus/          # Status bar component
├── patches/           # Applied patches directory
├── shell.nix          # NixOS development environment
├── Makefile           # Build script
└── README.md          # This file
```

---

## 🔧 Building from Source

### Standard Build

```bash
make clean      # Clean previous builds
make            # Compile dwm
make install    # Install to PREFIX
```

### With NixOS/Nix

```bash
nix-shell       # Enter development environment with dependencies
make clean install
```

---

## 📦 Patches Applied

This build includes the following enhancements:

- ✅ **actualfullscreen** - Proper fullscreen support
- ✅ **adjacenttag-skipvacant** - Skip empty workspaces when navigating
- ✅ **cool_autostart** - Flexible program autostarting
- ✅ **preserveonrestart** - Maintain window state across reloads
- ✅ **restartsig** - SIGHUP configuration reload support

---

## 🐛 Troubleshooting

### dwm crashes or behaves unexpectedly
→ Check your `config.h` for syntax errors and recompile: `make clean install`

### Black screen on startup
→ Ensure `xsetroot` is available and bar initialization isn't failing

### Fonts rendering incorrectly
→ Install FiraCode Nerd Font: 
```bash
sudo apt install fonts-noto fonts-noto-color-emoji fonts-firacode fonts-nerd-font-fira-code
```

### Keybindings not working
→ Verify your X modifier keys: `xev | grep -A2 "KeyPress"` and update `config.h`

### Status bar not updating
→ Ensure slstatus is running: `pgrep slstatus` (should return a PID)

---

## 💡 Tips & Tricks

### 1. **Persistent Dotfiles**
Create a dotfiles repository to version control your `config.h` and other configs

### 2. **Status Bar Script**
Create a custom status script instead of using slstatus:
```bash
#!/bin/bash
while true; do
  date "+%Y-%m-%d %H:%M:%S"
  sleep 1
done | xargs -I{} xsetroot -name "{}"
```

### 3. **Window Previews**
Use external tools like `xdotool` with keybindings for window management

### 4. **Multi-Head Setup**
Configure outputs in the autostart array using `xrandr`:
```bash
xrandr --output HDMI1 --mode 1920x1080 --right-of eDP1
```

---

## 📚 Resources & Documentation

- **Official dwm website**: [suckless.org/dwm](https://suckless.org/dwm)
- **Patches repository**: [suckless.org/dwm/patches](https://suckless.org/dwm/patches)
- **X11 Key Symbols**: `grep -r "XK_" /usr/include/X11/keysym.h`
- **Man pages**: `man dwm`

---

## 📄 License

dwm is released under the **MIT License**. See the LICENSE file for details.

---

## 🤝 Contributing

To contribute improvements:

1. Make changes to the source code
2. Test thoroughly with `make clean install`
3. Document your changes
4. Keep the spirit of "keep it simple" in mind

---

## 💬 Notes

This build is optimized for:
- ✅ Minimal resource usage
- ✅ Maximum keyboard-driven workflow
- ✅ Modern aesthetics with Nerd Font support
- ✅ Easy configuration and customization
- ✅ Seamless multi-monitor support

**Remember**: The philosophy of dwm is "do one thing and do it well." Enjoy the freedom of a keyboard-driven interface! ⌨️✨

---

<div align="center">

**Built with ❤️ for minimalists and power users**

*Make yourself comfortable. Code in C. Keep it simple.*

</div>
