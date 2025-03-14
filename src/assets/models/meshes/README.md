# Meshes

This directory stores the meshes used in this program. <br>
Each mesh type has its own sub-directory, containing 2 files, being:

## The Binary File (raw.bin)

The binary file contains the post parse version of the data from the .txt file (see below) <br>
This is just saved for speed purposes, dont edit this file.

## The Text File (readable.txt)

The text file contains a human readable format of the mesh data. This is where the meshes are created, and modified.

The format is as follows:

* This file format works mostly on tags, like `[tag]`
* The parser starts interpreting after the `[start]` tag
* Each other tag denotes a subsection of the file, and they are all followed by the count of items they contain, like `[tag-10]`
* Items under the tags have ids before them, like `0-someText` (ids start at 0)
* Semicolons are used to end any line, except tags
* All spaces are ignored, so `0 - text` is equivalent to `0-text`
* For vector formats, the commas are the seperators

### `[vertices-x]`

Each vertex has its position stored directly in vector form, like (x, y, z) <br>
Example vertex -> `0-(0.5, 0.5, 0.5)` or `0-(0.5,0.5,0.5)` (spaces are ignored)

### `[normals-x]`

Normals are stored just like vertices <br>
Example normal -> `0-(0, 1, 0)` or `0-(0,1,0)`

### `[tris-x]`

Tris are stored by pointing to items from the `[vertices]` and `[normals]` sections <br>
Each triangle is stored in 4d vector format, where the first 3 components are vertices and the last is the normal <br>
Example tri -> `0-(0, 1, 2, 0)` or `0-(0,1,2,0)`