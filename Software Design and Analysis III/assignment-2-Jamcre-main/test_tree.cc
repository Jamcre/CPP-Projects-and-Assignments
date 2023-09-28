// James Crespo
// Main file for Part2(b) of Homework 2.

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

namespace
{

  // @db_filename: an input database filename.
  // @seq_filename: an input sequences filename.
  // @a_tree: an input tree of the type TreeType. It is assumed to be
  //  empty.
  template <typename TreeType>
  void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree)
  {
    // Code for running Part2(b)

    //----------------Code for 1------------------

    string db_line;
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
    //------------End Code for 1------------------

    // 2. Total nodes in a tree
    cout << "2: " << a_tree.getNodeCount() << endl;

    // 3a. Average Depth of Tree = Total Depth / Total Nodes
    cout << "3a: " << float(a_tree.getDepthTotal()) / a_tree.getNodeCount() << endl;

    // 3b. Ratio =  Average Depth of Tree  / log2(Total Nodes)
    cout << "3b: " << float((a_tree.getDepthTotal()) / log2(a_tree.getNodeCount())) / a_tree.getNodeCount() << endl;

    //-------------Code for 4a and 4b-------------

    /* NOTE: I don't now if this was intentional but find() is not implemented in BST and AVL classes,
    Instead we have contains, which I think serves the same purpose, which is I will use contains() as find() */

    // Initialize counters
    int total_contains_calls = 0, total_searches = 0;

    // Initialize line reader, file object, and open into file object using filename param
    string seq_line;
    ifstream seq_file;
    seq_file.open(seq_filename);

    // Iterate through all lines in file
    while (getline(seq_file, seq_line))
    {
      // Create temp Seq_Map using line, and count contain() calls with helper
      SequenceMap temp_seq_map(seq_line);
      total_contains_calls += a_tree.getContainsCalls(temp_seq_map);

      if (a_tree.contains(temp_seq_map))
      {
        // Increment search counter for contains, returns true
        total_searches++;
      }
    }
    seq_file.close();

    //-----------End Code for 4a and 4b-----------

    // 4a. Total Number of Successful Queries (searches)
    cout << "4a: " << total_searches << endl;

    // 4b. Average Recursive Calls = Num of Recursion Calls / Num of Queries
    cout << "4b: " << float(total_contains_calls) / total_searches << endl;

    //-------------Code for 5a and 5b-------------

    // Initialize counters
    int line_num = 0, total_remove = 0;
    float tot_num_rem = 0;

    // Initialize line reader, file object, and open into file object using seq_filename param
    // NOTE: I made a 2nd set of variables, to keep Part 5 isolated from Part 4
    ifstream seq_file2;
    string seq_line2;
    seq_file2.open(seq_filename);

    // Loop to iterate through all lines in file
    while (getline(seq_file2, seq_line2))
    {
      // Conditional for skipping every other line
      if (line_num % 2 != 0)
      {
        line_num++;
        continue;
      }
      // Create temp Seq_Map object
      SequenceMap temp_seq_map2(seq_line2);
      // Check if Node, exists with contains(), to perform remove()
      if (a_tree.contains(temp_seq_map2))
      {
        // Perform remove
        a_tree.remove(temp_seq_map2);
        // increment total_remove, by checking if remove was successful, using contains()
        total_remove += !a_tree.contains(temp_seq_map2);
      }
      // Next line
      line_num++;
    }
    seq_file2.close();

    //-----------End Code for 5a and 5b-----------

    // 5a. Total Number of Successful Removes
    cout << "5a: " << total_remove << endl;

    // 5b. Average Recursive Calls = Num of Recursion Calls / Num of Remove Calls
    cout << "5b: " << tot_num_rem << endl;

    // 6a. Total Nodes in a Tree
    cout << "6a: " << a_tree.getNodeCount() << endl;

    // 6b. Average Depth of Tree = Total Depth / Total Nodes
    cout << "6b: " << float(a_tree.getDepthTotal()) / a_tree.getNodeCount() << endl;

    // 6c. Ratio =  Average Depth of Tree  / log2(Total Nodes)
    cout << "6c: " << float((a_tree.getDepthTotal()) / log2(a_tree.getNodeCount())) / a_tree.getNodeCount() << endl;
  }

} // namespace

int main(int argc, char **argv)
{
  if (argc != 4)
  {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST")
  {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  }
  else if (param_tree == "AVL")
  {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  }
  else
  {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
