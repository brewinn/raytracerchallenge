# Ray Tracer Challenge 
A WIP implementation of a ray tracer based on the book by Jamis Buck.

## Description

This project seeks to implement a ray tracer based on _The Ray Tracer
Challenge_ by Jamis Buck in C. Everything up to chapter 6 has been implemented
so far. While there is not a full ray-tracer just yet, the underlying elements are
falling into place. Additionally, three programs in the _main_ directory have been made which produce
images that can be seen in the _img_ folder. 

## Usage

This project is built on a Linux (Arch-based) distribution. It is not tested
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
- [ ] Chapter 7: Making a Scene
- [ ] Chapter 8: Shadows
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

- [x] Swap parameter order of _Canvas_WriteToPPM_ function
- [x] Change Makefiles to attain project's directory automatically
	- Used a workaround, must invoke Makefiles from their respective directories
- [x] Add _const_ modifiers were appropriate
- [x] Change Makefiles to be more resilient to added sources
- [ ] Add _Shape_ 'parent struct' to deal with multiple shapes
	- This probably won't be necessary until chapter 9
- [ ] Add _Shape_ pointer or similar identifier to _Intersection_
	- The end of chapter 6 implied that there should be a reference in _Intersection_

## Contributing

This is a personal project and hence is not seeking additional collaborators.
That said, code reviews and bug reports are welcome. If you find something
wrong, feel free to contact the current maintainer (brewinn@protonmail.com).

## License

The Unity Test Project files are licensed under the MIT license, see
_tests/Unity/license.txt_ for more information.

This rest of the project is licensed under GPL-3.0. For more information, see
the _LICENSE_ file in the project's root directory.

## Project Status

The project is currently in active development.
