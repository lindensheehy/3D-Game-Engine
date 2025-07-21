# Benchmarking Suite

This directory contains tools for benchmarking. The results of each test are written to `./results/output.txt` — overwriting any previous test results.

---

### Files Overview

#### `core.cpp`

Handles the benchmarking logic. You shouldn't need to modify this file.

#### `code.cpp`

Defines three key functions used by the benchmark runner:

- `void init()` – called once at the start.
- `void run()` – called each iteration.
- `void cleanup()` – called once after all iterations are complete.

Also defines the `iterations` variable, which controls how many times `run()` is called before timing results are logged.

This is where you put the logic that you want to benchmark.

#### `Run.bat`

Builds and runs the benchmarking executable.

This script requires `.o` files in `src/obj/`. It only needs the object files you reference — along with `graphics-gui-State.o` for timing.  

If you encounter linker errors, try running `build/BuildAll+Run.bat` first — it should populate the required object files in `src/obj/` and resolve the issue.
