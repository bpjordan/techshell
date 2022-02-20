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

Before a command is executed, arguments are tokenized and scanned for redirection operators (`<`, `>`, and `2>`). The argument
after each operator is passed to fopen. If fopen is successful, the tokens for the redirection operator and filename are removed
from the list of tokens, and the file descriptor of the opened file is saved for later use.

Once a new process is forked, all saved file descriptors are duplicated to their respective streams before exec() is called. This
way, only the forked process is affected by the redirection

### Builtin commands

- `ls` runs chdir on the current process rather than forking a new process
- `pwd` prints out the present working directory (which is already saved in a variable) without forking a new process
- `exit` exits the program, returning the exit value of the last process, according to convention.
