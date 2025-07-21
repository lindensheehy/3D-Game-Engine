# `src/src/graphics/gui/`

This directory contains all code related to windowing and input handling. It interfaces directly with the WinAPI and serves as a wrapper to simplify the OS-level interactions.

---

## Contents

- `GUI.cpp` — High-level entry point for the GUI module. Leverages both `State` and `Window`.
- `State.cpp` — Stores all state-related information for the window, including input events (mouse and keyboard) and time-related data.
- `Window.cpp` — Manages window creation, lifecycle, and destruction. Also handles generalized message routing to simplify other modules.

---

#### For more details, please refer directly to the code. The code is extensively commented, so most questions will likely be answered there.
