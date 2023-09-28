[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=11014425&assignment_repo_type=AssignmentRepo)
# Assignment-5-Code

To compile type:

 `make all`

To clean object files and executables type:

 `make clean`
 
To run the create and test graph routine, type:
`./CreateGraphAndTest <GRAPH_FILE> <ADJECENCY_QUERYFILE>`

where `<GRAPH_FILE>` is the file used to create the graph and
`<ADJECENCY_QUERYFILE>` is the file used to check if vertices
are adjacent

Example:
`./CreateGraphAndTest Graph1.txt AdjacencyQueries1.txt`

To run the find paths in graph routine, type:
`./FindPaths <GRAPH_FILE> <STARTING_VERTEX>`

where `<GRAPH_FILE>` is the file used to create the graph and 
`<STARTING_VERTEX>` is the vertex in the graph as the starting
point for the paths

Example:
`./FindPaths Graph2.txt 1`

# STUDENT PORTION

Parts of the assignment I completed: 
- Q1: Complete 
- Q2: Partial Complete(Maybe I can complete in time)

Bugs I encountered: 
- Q1 of the assignment had us implement a graph class and test with provided text files. This part of the program was mostly planning out exactly how to implement and I mostly spent my time deciding what I members I wanted in my class before actually coding anything. That helped me have an outline for what my class would look like in the end. I passed the 2 visible test casses for Q1, I hope my implementation is solid and I am able to pass the hidden test cases. Notable bugs/issues I faced were mostly due to the multiple data structures in this hw, this include incorrect member calls, unitended values being stored and sometimes not keeping track of what was stored. 

- Q2 of the assignment revolved around using Dijkstra's algorithm to find the shortest paths from given vertices to other vertices, I was not getting full credit for some visible test cases and see that I am printing the values of vertices in the wrong order. I will try to fix this before the due date but since I started late I will be cutting it close. Hopefully I can fix it in time. Bugs/Issues I encountered were mostly cause by me not fully grasping the algorithm and misreading the hw specifications. For example I missed the 'not_possible' in the unreachable vertices and had 'not possible' in my program. A small mistake that cost me a lot of points but I managed to fix it. UPDATE: I managed to get 10/10 on the test case, hopefully I pass the invisible ones

Instructions to run program:
- To run this program you use make all, to create the executables. Write statement './FindPaths GRAPH_FILE STARTING_VERTEX' or './CreateGraphAndTest GRAPH_FILE ADJECENCY_QUERYFILE' with the capital words being stand in for provided files. This will print in the terminal the request info. 
    EX: ./CreateGraphAndTest Graph1.txt AdjacencyQueries1.txt would print the starting vertex, ending vertex, and the weight of the edge that connects them

    EX: ./FindPaths Graph1.txt 1 would print end vertex, complete path to end vertex, and cost of the path

Input/Output files:
- Input: 
        Text Files: 
         Graph1.txt (Graph info)
         Graph2.txt (Graph info)

         AdjacencyQueries1.txt (Query info)
         AdjacencyQueries2.txt (Query info)

        Test Code:
         CreateGraphAndTest.cc (test file for Q1)
         FindPaths.cc (test file for Q2)
    
        
        Executable: 
         CreateGraphAndTest.o (Executable for Q1)
         FindPaths.o (Executable for Q2)

- Output: 
        Printed info on terminal
