# `src/src/xml/`

This directory contains a fully custom parser for an XML-like language. It is primarily used by the UI system to extract layout information from file data.  
For more details on the format of this language, see `src/assets/ui/README.md`.

---

## Contents

- `Core.cpp` — Global include for this module.
- `ElementSet.cpp` — Stores information about all recognized elements, using `ParameterInfo` and additional metadata.
- `ParameterInfo.cpp` — Defines the parameters associated with various elements and is used to validate them during construction.
- `TagSequence.cpp` — This is the primary IR for the XML data.
- `XML.cpp` — Main entry point for the XML module.
- `XMLFile.cpp` — Stores an entire XML file's data as a single structure.

---

#### For more details, please refer directly to the code. The code is extensively commented, so most questions will likely be answered there.
