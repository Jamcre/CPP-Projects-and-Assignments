// NAME: James Michael Crespo
// DESCRIPTION: Test file for Assignment 3
#include <fstream>
#include <iostream>
#include <string>

// Uncomment when you implemented linear probing & double hashing
#include "linear_probing.h"
#include "quadratic_probing.h"
#include "double_hashing.h"

using namespace std;
// You can add more functions here

// @hash_table: a hash table (can be linear, quadratic, or double)
// @words_filename: a filename of input words to construct the hash table
// @query_filename: a filename of input words to test the hash table
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table,
                              const string &words_filename,
                              const string &query_filename)
{
    // Empty hash table
    hash_table.MakeEmpty();

    // Initialize line readers and file objects
    string words_line, query_line;
    ifstream words_file, query_file;

    /*--------------------------------- PART A ---------------------------------*/
    // Open words file, Insert words from file into hash table, close file
    words_file.open(words_filename);
    while (getline(words_file, words_line))
    {
        hash_table.Insert(words_line);
    }
    words_file.close();
    // Print requested values of hash table from assignment
    std::cout << "number_of_elements: " << hash_table.getTotalElements() << std::endl; // Total Elements in Hash Table
    std::cout << "size_of_table: " << hash_table.getSize() << std::endl;               // Size of Hash Table
    std::cout << "load_factor: " << hash_table.getLoadFactor() << std::endl;           // Load Factor of Hash Table
    std::cout << "collisions: " << hash_table.getTotalCollisions() << std::endl;       // Total Collisions
    std::cout << "avg_collisions: " << hash_table.getAverageCollisions() << std::endl; // Average Collisions
    std::cout << std::endl;                                                            // Newline to show end of Part A

    /*--------------------------------- PART B ---------------------------------*/
    // Open query file, read queried word, check if present in hash table, close file
    query_file.open(query_filename);
    while (getline(query_file, query_line))
    {
        std::cout << query_line;              // Print queried word
        if (!hash_table.Contains(query_line)) // Case: Hash Table does not contain queried word
        {
            std::cout << " Not_Found ";
        }
        else // Case: Hash Table does contain queried word
        {
            std::cout << " Found ";
        }
        std::cout << hash_table.getTotalProbes() << std::endl; // Print how many probes needed to find queried word
    }
}

// @argument_count: argc as provided in main
// @argument_list: argv as provided in imain
// Calls the specific testing function for hash table (linear, quadratic, or double).
int testHashingWrapper(int argument_count, char **argument_list)
{
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 89;
    if (argument_count == 5)
    {
        const string rvalue(argument_list[4]);
        R = stoi(rvalue);
    }

    if (param_flag == "linear")
    {
        // Uncomment below when you have implemented linear probing.
        HashTableLinear<string> linear_probing_table;
        TestFunctionForHashTable(linear_probing_table, words_filename,
                                 query_filename);
    }
    else if (param_flag == "quadratic")
    {
        HashTable<string> quadratic_probing_table;
        TestFunctionForHashTable(quadratic_probing_table, words_filename,
                                 query_filename);
    }
    else if (param_flag == "double")
    {
        cout << "r_value: " << R << endl;
        // Uncomment below when you have implemented double hashing.
        HashTableDouble<string> double_probing_table;
        TestFunctionForHashTable(double_probing_table, words_filename,
                                 query_filename);
    }
    else
    {
        cout << "Unknown tree type " << param_flag
             << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv)
{
    if (argc != 4 and argc != 5)
    {
        cout << "Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag>" << endl;
        cout << "or Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
        return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}
