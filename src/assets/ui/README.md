  # `src/assets/ui/`

  This directory contains UI layout definitions for the engine’s custom UI system.

  Files are written in an XML-like markup language designed specifically for this project. While inspired by XML, the format is customized and slightly simplified to suit the engine’s unique requirements.

  ---

  ## Contents

  - `elements/` — Defines reusable UI element layouts. Think of these like macros: you define them once here, then reuse them anywhere else with ease. These layouts can’t be created on their own at runtime, since they include a `<parameters>` section.
  - `windows/` — Defines standalone UI window layouts. The main difference between these and the elements is the absence of a `<parameters>` section.

  ---

  ## Format

  - The syntax is XML-inspired but not fully compliant. For example:
    - Attribute values are unquoted.
    - Some non-standard syntax is allowed for ease of use.
  - Each file defines a window or element layout, broken into globally recognized sections:
    - `<parameters>` declares inputs for reusable components. Treat these like function parameters — you define what needs to be passed in, then use those freely within the layout.
    - `<labels>` defines constant values. Treat these like define macros — at parse-time, all instances of a label are swapped for the value declared.
    - `<main>` defines the main UI layout in a hierarchical structure.
  - Elements can nest arbitrarily and accept attributes that control positioning, size, color, and more (see `XML::initDefaultElements` and `XML::initCustomElements` in `src/src/xml/XML.cpp` for details on how attributes are handled).

  ---

  ## Key Notes

  - These XML files are parsed at runtime into in-memory objects.
  - The language is custom-built, and the parser lives in `src/include/xml/` and `src/src/xml/`.
  - This directory is actively used by the current build and is critical to engine interactivity.
  - In the case of a circular reference (via reusable elements with `<parameters>` sections), my code will halt parsing and throw an error. The current recursion limit is quite generous, so anything other than circular references should work properly (see `CALL_LIMIT` in `src/include/xml/XML.h` for details).
