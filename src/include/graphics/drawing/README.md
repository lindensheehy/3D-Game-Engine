# `src/include/graphics/drawing/`

This directory handles all 2D drawing within the application. It provides a high-level `Drawer` class for general-purpose 2D rendering, as well as a lower-level `PixelDrawer` class for more explicit, pixel-level control.

---

## Contents

- `Drawer.h` — High-level drawing interface, offering functions like `drawRect`, `drawLine`, and more.
- `PixelDrawer.h` — Low-level drawing interface, primarily used through `drawPixel`.
- `PixelTracker.h` — Supports object selection by tracking a specific pixel. Just a glorified data container.

---

## Dependencies

This section lists high-level **per-module relationships**.  
A module being listed here does *not* imply that **all files** in that module are involved —  
only that **one or more files** are directly included.

- `geometry/`
- `graphics/font/`
- `graphics/gui/`
- `graphics/rendering/`
- `util/`

---

#### For more details, please refer directly to the code. The code is extensively commented, so most questions will likely be answered there.
