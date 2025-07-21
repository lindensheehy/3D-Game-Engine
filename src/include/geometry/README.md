# `src/include/geometry/`

This directory contains all core geometry-related classes used by the engine, including vectors, triangles (unused in the current build), meshes, and matrices. It also includes a subdirectory intended for importing file-based mesh data, though this functionality is not yet implemented.

---

## Contents

- `importer/` — Contains tools for importing file-based meshes.
- `Matrix.h` — Defines a 4x4 matrix class, primarily used for graphics transformations.
- `Mesh.h` — Stores 3D mesh models.
- `Tri.h` — Defines `Tri2` and `Tri3` classes for 2D and 3D triangles, respectively.
- `Vec.h` — Defines `Vec2` and `Vec3` classes for 2D and 3D vectors, respectively.

---

## Dependencies

This section lists high-level **per-module relationships**.  
A module being listed here does *not* imply that **all files** in that module are involved —  
only that **one or more files** are directly included.

- `util/`

---

#### For more details, please refer directly to the code. The code is extensively commented, so most questions will likely be answered there.
