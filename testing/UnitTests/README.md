# Unit Tests

This directory contains a self-written unit testing framework used to validate the behavior of core functions. It's lightweight, modular, and outputs test results in a human-readable HTML format.

---

## Functions Tested

Currently covered:

- `sqrt`
- `sin`
- `cos`
- `tan`
- `arctan`
- `arcsin`
- `arccos`
- `normalize`
- `inRange`
- `getAngle`
- `floor`
- `round`

---

## How It Works

Each function is called multiple times with various inputs, and the output is compared to an expected result (calculated manually). A small margin of error is allowed for floating-point imprecision.

- Results are written to an HTML file (`./results/testreport.html`)
- The report opens automatically when running `Run.bat`
- Each test entry includes:
  - The function call
  - Expected vs. actual output
  - Pass/fail status
  - Margin of error (if applicable)

---

## Implementation Details

- A generic, templated `FunctionWrapper` class enables type-safe testing of any function signature.
- Supports variadic arguments using parameter packs (`args...`).
- Optional tolerance can be specified for approximate comparisons.
- All test logging is written using a simple HTML-based logger with custom styling for readability.

---

## Running Tests

To run the tests:

1. Navigate to the `UnitTests/` directory.
2. Run `Run.bat`.
3. Your browser should open automatically with the test report.
