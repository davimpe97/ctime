# ctime
Measures execution time of a target program for Windows operating systems.

## Description
Command-line program to measure execution of another program provided as correctly formatted argument.
The measurement is managed through the macros and functions of the time.h library.
The target program must be provided as path string, either complete or partial path, always according to the path search done by the CreateProcess() function.
Optional arguments for the target program can be provided, separated with whitespaces.
The file ctime.c allows for compiling of both an ASCII version and a Unicode version of the program.
The Unicode version can be compiled by defining the macro UNICODE.
###### WARNING: some compilers don't allow the usage of the wmain() function as entry point natively. Visual Studio does, mingw-gcc does not.

## Syntax
ctime (target path) (target arguments)

#### Argument
Takes strings (ASCII if UNICODE is not defined, Unicode otherwise) as argument.
#### Returns
EXIT_FAILURE if:

-a target is not provided;

-the length of the arguments exceeds the limit defined by the MAXLINE macro;

-the creation of the target process fails.

EXIT_SUCCESS otherwise.

##### Example
Let's suppose the execution time of a test.exe program, situated in the same folder as ctime.exe, should be measured, providing 1 as argument.
The command line should like:
###### ctime .\\\test.exe 1
