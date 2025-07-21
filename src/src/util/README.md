# `src/src/util/`

This directory contains generic yet essential code for the application. Many files here implement functionality normally provided by the STL, but due to project constraints, these have been custom-written and organized here.

---

## Contents

- `FileManager.cpp` — Intended as a low-level asset manager. Currently unused and incomplete.
- `FileNavigator.cpp` — File iterator system that wraps the WinAPI, supporting file tree traversal with optional recursive iteration.
- `FileReader.cpp` — Handles file reading using the WinAPI.
- `KeyCodes.cpp` — Defines a large enum of keycodes recognized by the application, along with helper functions.
- `Log.cpp` — Manages all logging in the app, using the WinAPI. Essentially a general purpose file output system, usable beyond logging purposes.
- `Math.cpp` — Fully custom math library, including square root, trigonometric functions, and other general-purpose math utilities.
- `Utility.cpp` — Intended as a global include for the entire project. Contains vital code such as type definitions and essential function declarations.

---

#### For more details, please refer directly to the code. The code is extensively commented, so most questions will likely be answered there.
