[![Tests](https://github.com/brewinn/raytracerchallenge/actions/workflows/tests.yml/badge.svg)](https://github.com/brewinn/raytracerchallenge/actions/workflows/tests.yml)
# Ray Tracer Challenge 
A WIP implementation of a ray tracer based on the book by Jamis Buck.

## Description

This project seeks to implement a ray tracer based on _The Ray Tracer
Challenge_ by Jamis Buck in C. Everything up to chapter 8 has been implemented
so far. While there is not a full ray-tracer just yet, the underlying elements are
falling into place. Additionally, five programs in the _main_ directory have
been made which produce images that can be seen in the _img_ folder. Note that
the programs where produced at the end of a particular chapter and may not
behave properly with the code from later chapters.

## Usage

This project is built on a Linux distribution. It is not tested
for Windows or MacOS.

Project can be run using one of the Makefiles in either the project root, the
_main_ directory, or the tests directory. Makefiles should be run from their
containing directory, so the Makefile at the project's root should be run with
the user's working directory at the project's root. The usage options of each
Makefile is given within the file itself. For example, running 

```
make
```

in the project's root directory will compile and run all tests and _main_
programs, then delete the test and program binaries. This will also fill the
_obj_ directory with compiled objects, which will make future compilations quicker. To
delete these, run

```
make cleanall
```

from any directory with a Makefile.

By default, images are placed in the directory of executable that created them. Images
in the _img_ directory are the results of previous compilations.

## Roadmap

- [x] Setup a testing framework
- [x] Add a makefile for easier building
- [x] Chapter 1: Tuples, Points, and Vectors
- [x] Chapter 2: Drawing on a Canvas
- [x] Chapter 3: Matrices
- [x] Chapter 4: Matrix Transformations
- [x] Chapter 5: Ray-Sphere Intersections
- [x] Chapter 6: Light and Shading
- [x] Chapter 7: Making a Scene
- [x] Chapter 8: Shadows
- [ ] Chapter 9: Planes
- [ ] Chapter 10: Patterns
- [ ] Chapter 11: Reflection and Refraction
- [ ] Chapter 12: Cubes
- [ ] Chapter 13: Cylinders
- [ ] Chapter 14: Groups
- [ ] Chapter 15: Triangles
- [ ] Chapter 16: Constructive Solid Geometry (CSG)
- [ ] Chapter 17: Next Steps

## TO-DO

This section contains a list of changes (mostly refactors) that are planned but not yet implemented.
Completed items will occasionally be pruned.

- [ ] Add _Shape_ 'parent struct' to deal with multiple shapes
	- This probably won't be necessary until chapter 9
- [x] Add warnings to compiler flags, and deal with them
- [x] Extract commonly used test functions to separate utility file
- [ ] Change memory allocation/deallocation to be more consistent and intuitive
    - I've changed some functions to help with memory, but this is an ongoing effort

## Contributing

This is a personal project and hence is not seeking additional collaborators.
That said, code reviews and bug reports are welcome. If you find something
wrong, feel free to contact the me (brewinn@protonmail.com).

## License

The Unity Test Project files are licensed under the MIT license, see
_tests/Unity/license.txt_ for more information.

This rest of the project is licensed under GPL-3.0. For more information, see
the _LICENSE_ file in the project's root directory.

## Project Status

Stalled. In the interest of further developing other projects, I'm setting this
project aside for the time being. Unfortunately, some quick experimentation has
suggested that a fairly large rework of the code is required, so it will be
some time before new features will be added.
