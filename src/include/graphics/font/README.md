# `src/include/graphics/font/`

This directory handles all font rendering for the application. It uses the `PixelDrawer` from the `drawing/` module to draw static font textures directly to the window. This implementation is minimal — it does not support anti-aliasing, font resizing, or other advanced features. It simply draws raw pixel maps to the screen.

---

## Contents

- `FontDrawer.h` — Handles font rendering.
- `Parser.h` — Currently empty. Intended to hold the parser for file-based font data.

---

## Dependencies

This section lists high-level **per-module relationships**.  
A module being listed here does *not* imply that **all files** in that module are involved —  
only that **one or more files** are directly included.

- `graphics/drawing/`
- `util/`

---

#### For more details, please refer directly to the code. The code is extensively commented, so most questions will likely be answered there.
