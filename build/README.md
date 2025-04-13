# Build Options

### `BuildAll+Run.bat`

**This is how you should build the app if you are running it for the first time**.

This just says builds everything. This will delete all existing `.o` files in `root/src/obj/`, and recompile each source file (`.cpp`), then run the app of course.

If youre not familiar with `.o` files, these are intermediate files that have been compiled, but are not yet executable. This is what my dependancies get compiled into, and they are linked in when `main.cpp` is compiled.

### `BuildPrimary+Run.bat` & `BuildMain+Run.bat`

**These are just intended for personal use, during development.**

`BuildPrimary` selectively compiles certain files based on what I'm working on at the time. This assumes most of the `.o` files already exist, and are valid. This is just used as a sort of 'quick build', because its quite time consuming recompiling all files on every build.

`BuildMain` just compiles and runs main, while including all the existing `.o` files. This is just meant for quick builds after changes to `main.cpp`

# Build System

**This has not been written yet, but I plan to make it soon.**
