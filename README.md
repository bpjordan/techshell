TechShell
=========

Completed as final project for CSC 222 (Systems Programming) at Louisiana Tech University

A shell which
- handles `pwd`, `cd`, and `exit` natively,
- supports I/O redirection for stdin, stdout, and stderr, and
- recognizes string arguments enclosed in `""`

Make Instructions
-----------------

The following `make` targets are provided:

- `make`: Default target compiles source with all warnings
- `make prod` : Production target which recompiles all objects using -O3 compiler flag
- `make debug`: Debug target which compiles any source which has changed to include debug messages and debugger optimization
- `make clean`: Removes all object files and test files

Implementation Details
----------------------

### I/O redirection

Before 
