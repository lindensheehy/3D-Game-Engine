# `testing/`

This directory contains tools used to validate performance and correctness of engine code. It is split into two main components: a **unit testing framework** and a **benchmarking suite**. Both are custom-built, lightweight, and tailored to the engine’s internal architecture.

---

## Contents

- `BenchMarking/` — Contains a benchmarking harness used to measure performance of arbitrary functions. Results are logged to a plain text file for easy inspection.
- `UnitTests/` — Contains a self-written unit testing framework that outputs human-readable HTML reports to verify function correctness.

---

## Key Notes

- This directory does not contribute to the current build. Both the benchmarking and unit tests exist exclusively for isolated testing.
