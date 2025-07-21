# `src/assets/fonts/`

This directory contains bitmap font files used for text rendering within the engine. While unused in the current build, it reflects the planned structure for future versions. Despite being inactive, the setup here is intentional and mostly complete.

Fonts are defined in human-readable `font.txt` files, alongside optional `raw.bin` files for faster loading post parse.

---

## Contents

- `7x7/` — Legacy bitmap font, stored as fixed-size 7x7 grids. This is the same font used in the current build, though it’s currently hardcoded into the binary.
- `32x32/` — A newer, high-resolution font format. Each character is a 32x32 grid, designed to be downsampled by the renderer for clean, scalable output. The font design itself is incomplete, but the structure is already in place.

---

## Format

- Each character block in the `.txt` files starts with a header tag like `[A]`, `[B]`, etc. (case-sensitive — `a` ≠ `A`)
- Characters are visually separated by `|` delimiters for readability (not parsed).
- `'█'` represents an active pixel (on), and `' '` represents an inactive pixel (off).
- Parsing begins after a `[start]` tag. Anything before this is ignored.

---

## Key Notes

- The `.bin` files are placeholders for now. Once the IR format is finalized, they’ll store serialized font data to reduce load times.
- The 7x7 font format is deprecated and will be replaced by the 32x32 version once the new renderer is ready.
