# Ray Tracer Challenge 
A WIP implementation of a ray tracer based on the book by Jamis Buck.

## Description

This project seeks to implement a ray tracer based on _The Ray Tracer
Challenge_ by Jamis Buck in C.  At the moment the project is just a skeleton,
but as the chapters are worked through over the next couple of weeks, we should
end up with a functional ray tracer.

## Usage

This project is built on a Linux (Arch-based) distribution. It is not tested
for Windows or MacOS.

Project can be run using one of the Makefiles in either the project root, the
src directory, or the tests directory. The _BASE_DIR_ variable will need to be
edited to reflect the path of the repository's root. The usage options of each
Makefile is given within the file itself. For example, running 

```
make
```

in the project's root directory will compile and run all tests and src
programs, then delete the test and program binaries. This will also fill the
obj file with compiled objects, which will make future compilations quicker. To
delete these, run

```
make cleanall
```

from any directory with a Makefile.

By default, images are placed in the directory of containing executable. Images
in the _img_ directory are the results of previous compilations.

## Roadmap

- [x] Setup a testing framework
- [x] Add a makefile for easier building
- [x] Chapter 1: Tuples, Points, and Vectors
- [x] Chapter 2: Drawing on a Canvas
- [x] Chapter 3: Matrices
- [x] Chapter 4: Matrix Transformations
- [ ] Chapter 5: Ray-Sphere Intersections
- [ ] Chapter 6: Light and Shading
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

- [ ] Swap parameter order of Canvas_WriteToPPM function
- [ ] Change Makefiles to attain project's directory automatically

## Contributing

This is a personal project and hence is not seeking additional collaborators.
That said, code reviews and bug reports are welcome. If you find something
wrong, feel free to contact the current maintainer.

## License

The Unity Test Project files are licensed under the MIT license, see
_tests/Unity/license.txt_ for more information.

This rest of the project is licensed under GPL-3.0. For more information, see
the _LICENSE_ file in the project's root directory.

## Project Status

The project is currently in active development.
