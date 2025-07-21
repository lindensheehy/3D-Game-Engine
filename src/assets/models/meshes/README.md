# `src/assets/models/meshes/`

This directory stores mesh data used by the engine. While unused in the current build, it reflects the planned structure for future versions. The setup here is intentional, but largely incomplete.

Each mesh type has its own subdirectory, where meshes are defined in human-readable `readable.txt` files, alongside optional `raw.bin` files for faster loading after the first load.

---

## Contents

- `cube/` — A simple regular cube. 6 square faces, forming 12 polygons. Normalized to side length 1 around the origin (0, 0, 0).
- `sphere/` — A sphere-like mesh. This approximates the shape of a sphere using 200 polygons. It is not a regular shape, instead using layers of interlacing triangles.

---

## Format

Mesh files follow a structured tag-based format, designed for both readability and easy parsing. Key characteristics:

- Tags are enclosed in square brackets: `[start]`, `[vertices-12]`, etc.
- The parser begins after the `[start]` tag.
- Subsections are labeled with a tag followed by a count, e.g. `[vertices-12]` for 12 vertices.
- Entries follow the format `id=value`, e.g. `0=(0.5, 0.5, 0.5)`
- Semicolons (`;`) end each line (except for tag headers).
- Whitespace is ignored, so `0 = (x, y, z)` is treated the same as `0=(x,y,z)`
- Vector values use comma separators.

---

### `[vertices-x]`

Each vertex stores a position vector in 3D space:

Example vertex: `0 = (0.5, 0.5, 0.5)`

### `[normals-x]`

Normals are stored just like vertices (but remember, these are **directions**, not positions):

Example normal: `0 = (0, 1, 0)`

### `[tris-x]`

Triangles reference existing vertices and normals. Each triangle is a 4D vector:

- The first three components are vertex indices
- The fourth component is the normal index

Example tri: `0 = (0, 1, 2, 0)`

---

## Key Notes

- Meshes must be defined in `readable.txt` first. The engine generates `raw.bin` from this source. These `.bin` files are not intended to be read, edited, or otherwise handled by humans.
- This directory is not currently used by the build. It exists to support future features in the engine’s asset loading system.
- The format is custom-built and may be updated depending on rendering needs going forward.