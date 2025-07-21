# `src/include/ui/`

This directory contains all code responsible for managing the UI system. The main entry point is the `UI` class, and in most cases, the other files can be ignored by users of the module.

However, when creating your own UI windows, you will need to edit BindFuncs and Context. That is, if you want the window to be interactive in any way.

---

## Contents

- `Action.h` — Defines simple classes for button actions.
- `BindFuncs.h` — Contains functions that define certain element behaviors upon interaction and actions for windows upon creation.
- `BindManager.h` — Manages links between active windows and functions from `BindFuncs`. This system powers the interactive layer of the UI.
- `Context.h` — Provides simple classes for passing data between `BindFuncs` and other parts of the code outside this module.
- `Core.h` — Global include file for this module.
- `UI.h` — Main entry point containing high-level functions for interacting with the UI system.
- `Window.h` — Defines individual UI windows.
- `WindowElement.h` — Defines various UI element types. These are polymorphic, with around 10 subclasses.

---

## Dependencies

This section lists high-level **per-module relationships**.  
A module being listed here does *not* imply that **all files** in that module are involved —  
only that **one or more files** are directly included.

- `geometry/`
- `graphics/drawing/`
- `graphics/gui/`
- `physics/`
- `util/`
- `xml/`

---

#### For more details, please refer directly to the code. The code is extensively commented, so most questions will likely be answered there.
