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

Currently, there is no makefile for automated building of the project. To use
what is currently in the project, compile, link, and run with whichever C
compiler you choose. 

For example, using the GNU's _gcc_ in the _tests_ directory:

```
gcc -I Unity Unity/*.c *.c -o TestOutput.test
```

This will compile and link the current tests. To run:

```
./TestOutput.test
```

## Roadmap

- [x] Setup a testing framework
- [] Add a makefile for easier building
- [] Chapter 1: Tuples, Points, and Vectors
- [] Chapter 2: Drawing on a Canvas

## Contributing

This is a personal project and hence is not seeking additional collaborators.
That said, code reviews and bug reports are welcome. If you find something
wrong, feel free to contact the current maintainer.

## License

The Unity Test Project files are licensed under the MIT license, see
tests/Unity/license.txt for more information.

This rest of the project is licensed under GPL-3.0. For more information, see
the LICENSE file in the project's root directory.

## Project Status

The project is currently in active development.
