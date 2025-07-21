# `src/include/xml/`

This directory contains a fully custom parser for an XML-like language. It is primarily used by the UI system to extract layout information from file data.  
For more details on the format of this language, see `src/assets/ui/README.md`.

---

## Contents

- `Core.h` — Global include for this module.
- `ElementSet.h` — Stores information about all recognized elements, using `ParameterInfo` and additional metadata.
- `ParameterInfo.h` — Defines the parameters associated with various elements and is used to validate them during construction.
- `TagSequence.h` — This is the primary IR for the XML data.
- `XML.h` — Main entry point for the XML module.
- `XMLFile.h` — Stores an entire XML file's data as a single structure.

---

## Dependencies

This section lists high-level **per-module relationships**.  
A module being listed here does *not* imply that **all files** in that module are involved —  
only that **one or more files** are directly included.

- `ui/`
- `util/`

---

#### For more details, please refer directly to the code. The code is extensively commented, so most questions will likely be answered there.
