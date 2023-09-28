[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10961430&assignment_repo_type=AssignmentRepo)
# Assignment-4-Code

Parts of the assignment I completed: 
- Part 1: Complete 
- Part 2: Partial Completion
- Part 3: Complete

Bugs I encountered: 
- The 1st part of the assignment was mostly straight forward, following the changes that were listed on the assignment was most of what this part revolved around. Most of the work was looking at the already implemented functions, and deciding what needed modification and what could be left alone based on the outlined changes. 

- The 2nd part was where I found some issues. Remove() in binomial_queue.h was giving me issues when testing. My out2.txt file was not matching with the provided results. Since this part revolved around Remove(), I where my issue was. I believe the issue probably lies with the parent pointer that was added to the BinomialNode. I looked around the implementation for places I may have missed adding the parent pointer, or perhaps added it to somewhere it doesn't belong. Ultimately, I decided to move onto Part 3 because I hit a wall here. 

- The 3rd part was hard to understand at first, but I found that drawing out the interactions help me visualize task. Overall, it checks X is not in the table, then it creates a temporary Binomial node, finds an empty space in the vector of trees, combines the temp Node and the trees(if required), performs insertion and updates privately variables where required. 

Instructions to run program:
- To run this program you use make all, to create the executables. After you write a statement, like the one that follows './test_insert_and_search 100_numbers.txt 100_test_search.txt > out1.txt'. This specific line will test Part 1 of the assignment on the text file with 100 integers and write result to the file out1.txt, after this point you are meant to compare out1.txt to 100_search_out.txt, if the values in the files match, the binomial queue and hashtable are working correctly. You can modify the intial command to test other parts of the assignement with other number.txt files. Another example is as follows, 
'./test_new_insert 20_numbers.txt 20_test_search.txt > out3.txt', this line tests Part 3 of the assignment with a 20 int text file for the queue, and a test file to check, writes result into out3.txt. There are various commands that could be made to perform different test on different parts of the assignment.

Input/Output files:
- Input: 
        Text Files: 
         x_numbers.txt (where x = 20, 100, 1000)
         x_test_search.txt (where x = 20, 100, 1000)
         x_test_delete.txt (where x = 20, 100, 1000)

        Test Code:
         test_insert_and_search.cc (test file for part 1)
         test_insert_and_delete.cc (test file for part 2)
         test_new_insert.cc (test file for part 3)
        
        Executable: 
         test_insert_and_search.o (Executable for part 1)
         test_insert_and_delete.o (Executable for part 2)
         test_new_insert.o (Executable for part 3)


- Output: 
        Text Files: 
         out1.txt (Results for Part1 implementation)
         out2.txt (Results for Part2 implementation)
         out3.txt (Results for Part3 implementation)
