# `src/include/graphics/gui/`

This directory contains all code related to windowing and input handling. It interfaces directly with the WinAPI and serves as a wrapper to simplify the OS-level interactions.

---

## Contents

- `Core.h` — Shared utilities and definitions used throughout this module.
- `GUI.h` — High-level entry point for the GUI module. Leverages both `State` and `Window`.
- `State.h` — Stores all state-related information for the window, including input events (mouse and keyboard) and time-related data.
- `Window.h` — Manages window creation, lifecycle, and destruction. Also handles generalized message routing to simplify other modules.

---

## Dependencies

This section lists high-level **per-module relationships**.  
A module being listed here does *not* imply that **all files** in that module are involved —  
only that **one or more files** are directly included.

- `graphics/drawing/`
- `graphics/rendering/`
- `util/`

This module also depends on `<windows.h>`.

---

#### For more details, please refer directly to the code. The code is extensively commented, so most questions will likely be answered there.
