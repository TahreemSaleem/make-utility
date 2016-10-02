Create a makefile for the matrix/vector multiplication code (using pthreads) that you wrote in an
earlier lab. At the very least, divide your code into vector.h, vector.cc, matrix.h,
matrix.cc, and a main.cc files. The makefile should specify rules for compiling your code
into object files, and then linking the object files into an executable binary called matrix.out.
Specify all file dependencies in the makefile and make sure you provide the flags to include the
pthreads library when invoking the GCC compiler.