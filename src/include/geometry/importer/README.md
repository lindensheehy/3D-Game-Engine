## This module has been postponed until V2

# Mesh Importer

This directory contains code for importing Mesh objects from files.
This will default to using the `raw.bin` file, unless it does not exist or is empty.
If the `raw.bin` file is not valid, this will use the `readable.txt` file, and generate a cooresponding binary file.
You can also force a reload by deleting the contents of `raw.bin`.