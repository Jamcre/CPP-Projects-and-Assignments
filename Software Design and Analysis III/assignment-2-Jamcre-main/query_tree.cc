// James Crespo
// Main file for Part2(a) of Homework 2.

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

namespace
{
  // @db_filename: an input filename.
  // @a_tree: an input tree of the type TreeType. It is assumed to be empty.
  template <typename TreeType>
  void QueryTree(const string &db_filename, TreeType &a_tree)
  {
    /* Code for running Part2(a), use public functions of TreeType(AVL or BST) */
    // Open file, and intialize line-reader string and file object
    string db_line, input;
    ifstream db_file;
    db_file.open(db_filename);
    // Read file line-by-line
    while (getline(db_file, db_line))
    {
      string temp_str, a_reco_seq, an_enz_acro;
      bool check = false;
      // Iterate through db_line, by char, using index
      for (size_t i{0}; i < db_line.size(); i++)
      {
        // Case where an_enz_acro is found, and parsing for a_reco_seq begins
        if (db_line[i] == '/' && !check)
        {
          an_enz_acro = temp_str;
          temp_str.clear();
          check = true;
        }
        // Case where an_enz_acro and a_reco_seq is complete,
        // temp SequenceMap is initialized, and added to tree
        else if (db_line[i] == '/')
        {
          if (!temp_str.empty())
          {
            a_reco_seq = temp_str;
            temp_str.clear();
            SequenceMap temp_seq_map(a_reco_seq, an_enz_acro);
            a_tree.insert(temp_seq_map);
          }
        }
        // Case to add chars to temp_str, temp_str being a_reco_seq or an_enz_acro
        else
        {
          temp_str += db_line[i];
        }
      } // End for-loop
    }   // End while-loop
    db_file.close();

    // User queries tree, using recognition sequence
    cout << "Enter Reco Seq strings: " << endl;
    while (getline(cin, input))
    {
      SequenceMap temp_seq_map2(input);
      if (a_tree.contains(temp_seq_map2))
      {
        cout << a_tree.getEnzAcro(input) << endl;
      }
      else
      {
        cout << "Not Found" << endl;
      }
    } // End while-loop
  }   // End QueryTree
} // namespace

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST")
  {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  }
  else if (param_tree == "AVL")
  {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  }
  else
  {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
