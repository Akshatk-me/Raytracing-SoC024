# RAY TRACING PROJECT IN CPP

This is the raytracing project made for Summer of Code 2024 by me.

We are following [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html). 

## Building the Project 
First you should clone the repository.

Now there are two ways you can build this 
1. Using Makefile
2. Using cmake 

I suggest the cmake method as it ensures better cross compatibility between platforms.

### Building using Makefile 
- `cd` into this repository. 
- Run `make` 

A binary called `bin` is the executable prepared ready to run.

### Building using cmake 
- `cd` into this repository. 
- run `cmake -S src/ -B build/` (the actual way to specify directory paths may vary)
- `cd` into the `build` directory.
- Run `make`


A binary called `bin` is the executable prepared ready to run.



