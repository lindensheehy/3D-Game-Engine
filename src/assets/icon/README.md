# `src/assets/icon/`

This directory contains the icon files used for Kiwi3D, along with the `resource.rc` file that embeds the icon into the binary as a Windows resource.

The icon is a simple digital sketch of a kiwifruit. And yes, I drew it myself 😄

---

## Contents

- `Kiwi3D-icon.ico` — The main icon file associated with this app. Includes multiple resolutions for different UI contexts (taskbar, window title bar, Alt+Tab).
- `KiwiIcon.png` — The original PNG sketch of my kiwifruit icon. Converted to `.ico` using an online tool.
- `resource.rc` — The resource script that instructs the compiler to embed the icon into the executable.

---

## Key Notes

- At compile time, the resource script is compiled to an object (`.o`) file using a resource compiler (`windres`, in my case), which is then linked into the executable for use at runtime.
