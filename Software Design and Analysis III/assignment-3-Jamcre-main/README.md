## Student Portion of README

Parts of the assignment I completed: 
- All of them, except my code has an issue with Parsing in Part III, causing me to not pass the 'Correct or Incorrect' test case

Bugs I encountered: 
- I encountered some bugs during the creation of my double_hashing.h file and linear_probing.h file, since they both contain almost the same implementations as quadratic_probing.h with the exception of some methods. I found that I would sometimes rewrite functions incorrect, whether this be the logic in the function, or forgetting to add parameters. This took a decent amount of time to fix because it was hard to detect this during testing, all which could've been avoided if I thoroughly read the assignment.

- Another issue I found was during the spell checker portion of the assignment. To perform the Cases we were assigned, I created a helper function 'cleanString' that would make a string, lowercase, remove spaces and remove punctuation after/before the word. I made the error of removing all punctuation, even the things within a word. This lead to words being Correct/Incorrect when the shouldn't be. An example of this, I found during testing was the word "Patel's", when I used my string cleaner, it would result in patels, when it should result in patel's. This took a while to fix aswell because I did not think to look here for an error. I was so certain that my issues were in the implementations of helper functions for Case A-C, that it made me waste a decent amount of time. All of this wasted time could've been avoided if I thoroughly read the assignment specifications.

- The R-value used for Part 2, double hashing was 89. I remembered from the lectures that R values for the second hash function should be prime becasue it can help to distribute the keys more evenly across the hash table. I realized this when I didn't pass all tests for double hashing in the grader when I was using other prime numbers in the autograder

Instructions to run program:
- Have quadratic_probing.h, linear_probing.h, double_hashing.h, create_and_test_hash.cc. In the cc file, read in test txt files with words to populate the dictionary, Then the cc test file will output information about the dictionary such as total elements, load factor etc. You can also query words to test dictionary efficieny, displayed through probe counters
- To run spell_check.cc, Have the double_hashing.h file above, and a text to spell. Populate the dictionary with words to check against, and then the spell_check.cc will parse through the text, grabbing each word and comparing against the stored words to determine if it is correct/incorrect

Input/Output files:
- Input: double_hashing.h, linear_probing.h, quadratic_probing.h, spell_check.cc, and create_and_test_hash.cc. Also include text files so these files can populate dictionaries, query words from texts, and spellcheck texts
- Output: Executables, and prints out Hash table metrics, and results from queries /  spell checks