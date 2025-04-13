# Bench Marking Suite

The files in this directory are used for benchmarking. The output of these tests is printed to a .txt file under `results/output.txt`

### `core.cpp`

Contains the logic for bench marking. No need to touch this file.

### `code.cpp`

Contains the two functions that are called from `core.cpp`. Those being `void init()` and `void run()`. 

`init()` is called once when the bench marking starts.
`run()` is called on each iteration

Also contains the variable `iterations`, which says how many times the code will call `run()` before logging the time elapsed.