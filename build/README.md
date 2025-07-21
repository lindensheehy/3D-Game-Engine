# `build/`

This directory contains the files to build and run SceneLab3D. The options are as follows:

---

## If you're running the app for the first time

### `BuildAll+Run.bat`

This script builds everything. It will delete all existing `.o` files in `root/src/obj/`, recompile each source file (`.cpp`), and then run the app.

If you're not familiar with `.o` files — these are intermediate object files that have been compiled, but are not yet executable. My dependencies are compiled into these `.o` files, and then linked in when `main.cpp` is compiled.

---

## For development use

### `BuildPrimary+Run.bat`

- selectively compiles certain files based on what I'm working on at the time. It assumes most of the existing `.o` files are still valid. It's basically a "quick build" option to save time by avoiding full recompilation.

### `BuildMain+Run.bat`

- compiles and runs just `main.cpp`, linking in all the existing `.o` files. This is useful for testing quick changes made directly to `main.cpp`.

---

## 🧰 Build Requirements

This engine is **Windows-only** and depends on `windows.h`.

- **Compiler**: GCC via MinGW (uses `g++` under the hood)
- **Architecture**: Built and tested for **x86_64 (64-bit)** systems
- **Optimization**: Compiled with `-Ofast` for speed
- **Standard**: Written for **C++17**

⚠️ **Note**: This project has very limited testing outside my own development environment.  
Your mileage may vary depending on your compiler version or system configuration.