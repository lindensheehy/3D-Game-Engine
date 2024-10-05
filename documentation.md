# Documentation

The following is some info about various parts of the code, mostly just so I can remember key things after I come back here from a long break, but if you're not me thats cool too.
The stuff here is more or less in the order it was built, and the hierarchical order (things below rely on things above)

## Log.h

**Contains functions** - logInit, logClear, logNewLine, logWrite, logVar

These functions are used to output text to the file "log.txt"
I decided to make this becuase i was having trouble debugging via the console, and since a text file has the ability to store much more data, plus the ability to ctrl+f, I thought it would be much nicer.
This is one of the only files which directly uses libraries not written by me, those being: 'iostream', 'iomanip', and 'fstream'

## Math.h

**Relies on** - Log.h
**Contains functions** - floor, round, sqrt, sin, cos, tan, arcsin, arccos, arctan, distance2, distance3, range, inRange, swap, getAngle, toRadians, toDegrees, min, max

Rather than using a math library like 'cmath', I wrote this to accomplish all the tasks I would want from something else.
Most of the stuff here is straightforward, and those that arent are well documented in the comments of the source file (src/src/math.cpp) so check that out for all the trig functions and sqrt.

## LinkedList.h

**Relies on** - Log.h
**Contains classes** - LinkedList

This is a general doubly linked list class which has a template allowing it to use any type inside.
At the moment this simply has all the source code in this header file, but now that im using it in more than one place I really should give it a designated source file

## Gui.h

**Relies on** - Log.h, SDL.h
**Contains classes** - Gui

placeholder

## Vec.h

**Relies on** - Log.h, Math.h
**Contains classes** - Vec2, Vec3


These classes hold vectors as sets of double values in two and three dimensions for Vec2 and Vec3 respectively.
Both of these also contain a magnitude value which is only updated when asked for. Because this value is held privately, it can only be used via the 'magnitude' function.

## State.h

**Relies on** - Log.h, Math.h, SDL.h
**Contains classes** - State

This is a class for storing the state of everything on any given frame, as well as the previous frame. This includes keypresses, mouse button presses, mouse position, and everything time related.
This is also one of the only files which uses a library not written by me, that being 'chrono'

## Tri.h

**Relies on** - Log.h, Math.h, Vec.h
**Contains classes** - Tri2, Tri3

placeholder

## Mesh.h

**Relies on** - Log.h, Math.h, Vec.h, Tri.h, SDL.h
**Contains classes** - Mesh

placeholder

## Camera.h

**Relies on** - Log.h, Math.h, Vec.h, Tri.h, Mesh.h, SDL.h
**Contains classes** - Camera, Display

placeholder

## Drawer.h

**Relies on** - Log.h, Math.h, LinkedList.h, Vec.h, State.h, Tri.h, Mesh.h, Camera.h, SDL.h
**Contains classes** - Color, PNG, Drawer

placeholder