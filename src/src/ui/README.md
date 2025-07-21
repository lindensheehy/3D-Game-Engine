# `src/src/ui/`

This directory contains all code responsible for managing the UI system. The main entry point is the `UI` class, and in most cases, the other files can be ignored by users of the module.

However, when creating your own UI windows, you will need to edit BindFuncs and Context. That is, if you want the window to be interactive in any way.

---

## Contents

- `Action.cpp` — Defines simple classes for button actions.
- `BindFuncs.cpp` — Contains functions that define certain element behaviors upon interaction and actions for windows upon creation.
- `BindManager.cpp` — Manages links between active windows and functions from `BindFuncs`. This system powers the interactive layer of the UI.
- `Core.cpp` — Global include file for this module.
- `UI.cpp` — Main entry point containing high-level functions for interacting with the UI system.
- `Window.cpp` — Defines individual UI windows.
- `WindowElement.cpp` — Defines various UI element types. These are polymorphic, with around 10 subclasses.

---

#### For more details, please refer directly to the code. The code is extensively commented, so most questions will likely be answered there.
