# `src/include/util/`

This directory contains generic yet essential code for the application. Many files here implement functionality normally provided by the STL, but due to project constraints, these have been custom-written and organized here.

---

## Contents

- `FileManager.h` — Intended as a low-level asset manager. Currently unused and incomplete.
- `FileNavigator.h` — File iterator system that wraps the WinAPI, supporting file tree traversal with optional recursive iteration.
- `FileReader.h` — Handles file reading using the WinAPI.
- `KeyCodes.h` — Defines a large enum of keycodes recognized by the application, along with helper functions.
- `LinkedList.h` — Templated doubly linked list with an internal iterator for general use.
- `Log.h` — Manages all logging in the app, using the WinAPI. Essentially a general purpose file output system, usable beyond logging purposes.
- `Math.h` — Fully custom math library, including square root, trigonometric functions, and other general-purpose math utilities.
- `Utility.h` — Intended as a global include for the entire project. Contains vital code such as type definitions and essential function declarations.

---


## Dependencies

This section lists high-level **per-module relationships**.  
A module being listed here does *not* imply that **all files** in that module are involved —  
only that **one or more files** are directly included.

- *NONE*

This module also depends on `<windows.h>`.

---

#### For more details, please refer directly to the code. The code is extensively commented, so most questions will likely be answered there.
