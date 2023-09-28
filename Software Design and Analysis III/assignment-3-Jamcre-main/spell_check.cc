// NAME: James Michael Crespo
// spell_check.cc: A simple spell checker.

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "double_hashing.h"
using namespace std;

/*----------------------------------------HELPERS-----------------------------------------*/

/*
  Returns a cleaned string, Example below
  Input: "THIS is a @Test ??? STRING !!""
  Ouput: "thisisateststring"
*/
void cleanString(string &str)
{
  // Convert all characters of str to lowercase
  transform(str.begin(), str.end(), str.begin(), ::tolower);

  // Remove all whitespace from str
  str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());

  // Remove all , . ! characters, from beginning and end of str
  str.erase(0, str.find_first_not_of(" .,!"));
  str.erase(str.find_last_not_of(" .,!") + 1);
}
/*-----------------------------------------CASES------------------------------------------*/

// CASE A: Adding one character in any possible position
vector<string> performCaseA(const string &str, char letter)
{
  vector<string> modified_words;
  // Iterates through all positions in str
  for (size_t i = 0; i <= str.size(); i++)
  {
    // Add letter to str based on i position, and adds to vector
    modified_words.emplace_back(str.substr(0, i) + letter + str.substr(i));
  }
  // Return vector with all possible modifications
  return modified_words;
}

// CASE B: Removing one character from the word
vector<string> performCaseB(const string &str)
{
  vector<string> modified_words;
  // Iterates through all positions in str
  for (size_t i = 0; i < str.size(); ++i)
  {
    // Add copy of str to modified words
    modified_words.emplace_back(str);
    // Remove the character at the current position, using .back() to access copy in the vector
    modified_words.back().erase(i, 1);
  }
  // Return vector with all possible modifications
  return modified_words;
}

// CASE C: Swapping adjacent characters in the word
vector<string> performCaseC(const string &str)
{
  vector<string> modified_words;
  // Iterates through all positions in str, except last (last char can't be swapped, since it's last char)
  for (size_t i = 0; i < str.size() - 1; ++i)
  {
    // Swap the current character with the next one
    string modified_word = str;
    swap(modified_word[i], modified_word[i + 1]);
    // Add modified word to the vector
    modified_words.push_back(modified_word);
  }
  // Return vector with all possible modifications
  return modified_words;
}
/*------------------------------------------END-------------------------------------------*/

// Creates and fills double hashing hash table with all words from dictionary_file
HashTableDouble<string> MakeDictionary(const string &dictionary_file)
{
  HashTableDouble<string> dictionary_hash;
  // Initialize line readers and file objects,
  string dictionary_file_line;
  ifstream dictionary;
  dictionary.open(dictionary_file);
  // Read each line, get word, insert into dictionary
  while (getline(dictionary, dictionary_file_line))
  {
    dictionary_hash.Insert(dictionary_file_line);
  }
  return dictionary_hash;
}

// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(const HashTableDouble<string> &dictionary,
                  const string &document_file)
{
  // Initialize line readers and file objects,
  string current_word;
  ifstream document;
  document.open(document_file);
  // Read through document, grab each word, check dictionary.
  // NOTE: delimeter is ' ' b/c, it has multiple words per line
  while (getline(document, current_word, ' '))
  {
    // Prepare string for comparisons
    cleanString(current_word);
    // Check if current_word not empty
    if (current_word.size() > 0)
    {
      if (dictionary.Contains(current_word)) // Case: current_word is in dictionary
      {
        cout << current_word << ' is CORRECT' << endl;
      }
      else // Case: current_word is not in dictionary
      {
        cout << current_word << ' is INCORRECT' << endl;

        // Perform Case A: Adding one character in any possible position to current_word,
        // and check if modified word in dictionary.
        for (char letter = 'a'; letter <= 'z'; letter++) // Iterates through all lowercase letters
        {
          // Iterates through all modified words in vector created by perfomingCaseA on current letter
          for (const auto &modified_wordA : performCaseA(current_word, letter))
          {
            // Checks if current index in vector exists in dictionary
            if (dictionary.Contains(modified_wordA))
            {
              // Output if Successful
              std::cout << "** " << current_word << " -> " << modified_wordA << " ** case A" << endl;
            }
          }
        }

        // Perform Case B: Removing one character in all positions of current_word, and check in dictionary
        // Iterates through all modified words in vector created by perfomingCaseB on current_word
        for (const auto &modified_wordB : performCaseB(current_word))
        {
          // Checks if current index in vector exists in dictionary
          if (dictionary.Contains(modified_wordB))
          {
            // Output if Successful
            cout << "** " << current_word << " -> " << modified_wordB << " ** case B" << endl;
          }
        }

        // Perform Case C: Swapping adjacent characters in current_word, check if modified word in dictionary.
        // Iterates through all modified words in vector created by perfomingCaseC on current_word
        for (const string &modified_wordC : performCaseC(current_word))
        {
          if (dictionary.Contains(modified_wordC))
          {
            // Output if Successful
            cout << "** " << current_word << " -> " << modified_wordC << " ** case C" << endl;
          }
        }
      }
    }
  }
}

// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char **argument_list)
{
  const string document_filename(argument_list[1]);
  const string dictionary_filename(argument_list[2]);

  // Call functions implementing the assignment requirements.
  HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
  SpellChecker(dictionary, document_filename);

  return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }

  testSpellingWrapper(argc, argv);

  return 0;
}
