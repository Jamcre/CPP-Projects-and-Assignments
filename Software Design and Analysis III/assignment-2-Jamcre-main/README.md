[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10164961&assignment_repo_type=AssignmentRepo)
# Assignment 2

You will use this exact `Makefile` for your Homework 2. Failure to do so will result in *deduction* of points. Replace this file with a `README.md` for your own project. You can move these instructions to the bottom of the file if you wish.

To compile on terminal, type:

```bash
make all
```

You can compile one program individually by just typing `make <Program Name>`, for example:

```bash
make query_tree
```

To delete executables and object files, type:

```bash
make clean
```

Always perform make clean before make all.

## Student Portion of README

Parts of the assignment I completed: All of them, except 5b

Bugs I encountered: 
- Most of my issues came from moving implementations from BST to AVL files and vice versa. I would work on one file and move it over to the other file, and a semi-colon or parenthesis or something small would get left behind. This would sometimes have me stuck because it would be a small syntax error and there is so much to scroll through in each file. 
- A bug I had was properly recording the recursive calls for find()(really contains()) and remove(). Getting the proper amount of recursive calls was difficult because recursion is a dificult concept to understand for me, unless I draw out each call and track it visually.

Instructions to run program:
- make sure bst_tree.h and avl_tree.h are implemented correctly. Run test_tree.cc or query_tree.cc

Input/Output files:
- Input: bst_tree.h, avl_tre.h, and any text files used to read recognition sequences and enzyme acronyms.
- Output: Executable, and any output text files