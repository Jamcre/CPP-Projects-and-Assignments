[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=9965153&assignment_repo_type=AssignmentRepo)
# Assignment 1

## Information about the repository

This repository contains the following:
- Starter code: `points2d.h`, `test_points2d.cc`,`test_input_file.txt`, `expected_output.txt`, `Makefile` and `README.md`
- Assignment specification: `Spring23-Assignment1.pdf`

## Running the assignment

You will use this exact `Makefile` for your Assignment 1. Failure to do so will result in *deduction* of points.

To compile on terminal, type:

```bash
make clean
make all
```

To delete executables and object files, type:

```bash
make clean
```

To run, type:

```bash
./test_points2d
```

## Providing Input from Standard Input

To run with a given file that is redirected to standard input:

```bash
./test_points2d < test_input_file.txt
```

## Student Portion of README

Parts of the assignment I completed: All of them

Bugs I encountered: 
- When I created stubs, for this program I initialized size_ in the one-paramater constructer with a 0 instead of a 1. Took forever to find because it was such a trivial mistake.
- Some conflicts when using int type to access the array 'sequence_', because size() returns a size_t type which conflicts sometimes with int

Instructions to run program:
- initialize an object using my class, the object is essentially a 2D array 
- use supported member functions, to achieve any goal the user has with this object

Input/Output files:
- Input: None besides the provided test files
- Output: None besides executable
