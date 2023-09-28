// NAME: James Michael Crespo
// DESCRIPTION: The implementation file for BinomialQueue
#ifndef BINOMIAL_QUEUE_H
#define BINOMIAL_QUEUE_H

#include <iostream>
#include <vector>
#include "dsexceptions.h"
// Include HashTable file
#include "quadratic_probing.h"

using namespace std;

// Binomial queue class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( )           --> Return and remove smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void merge( rhs )      --> Absorb rhs into this heap
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinomialQueue
{
public:
  BinomialQueue() : theTrees(DEFAULT_TREES)
  {
    for (auto &root : theTrees)
      root = nullptr;
    currentSize = 0;
  }

  BinomialQueue(const Comparable &item) : theTrees(1), currentSize{1}
  {
    theTrees[0] = new BinomialNode{item, nullptr, nullptr};
  }

  BinomialQueue(const BinomialQueue &rhs)
      : theTrees(rhs.theTrees.size()), currentSize{rhs.currentSize}
  {
    for (int i = 0; i < rhs.theTrees.size(); ++i)
      theTrees[i] = clone(rhs.theTrees[i]);
  }

  BinomialQueue(BinomialQueue &&rhs)
      : theTrees{std::move(rhs.theTrees)}, currentSize{rhs.currentSize}
  {
  }

  ~BinomialQueue()
  {
    makeEmpty();
  }

  /**
   * Deep copy.
   */
  BinomialQueue &operator=(const BinomialQueue &rhs)
  {
    BinomialQueue copy = rhs;
    std::swap(*this, copy);
    return *this;
  }

  /**
   * Move.
   */
  BinomialQueue &operator=(BinomialQueue &&rhs)
  {
    std::swap(currentSize, rhs.currentSize);
    std::swap(theTrees, rhs.theTrees);

    return *this;
  }

  /**
   * Return true if empty; false otherwise.
   */
  bool isEmpty() const
  {
    return currentSize == 0;
  }

  /**
   * Returns minimum item.
   * Throws UnderflowException if empty.
   */
  const Comparable &findMin() const
  {
    if (isEmpty())
      throw UnderflowException{};

    return theTrees[findMinIndex()]->element;
  }

  /**
   * Insert item x into the priority queue; allows duplicates.
   */
  /* Change c: change return type to bool */
  bool insert(const Comparable &x)
  {
    if (positions_table_.Contains(x)) // x found, no insertion
    {
      return false;
    }
    else // x not found, insert x
    {
      BinomialQueue oneItem{x};
      // perform insertion
      positions_table_.Insert(x, oneItem.theTrees[0]); // params are key, value
      merge(oneItem);
      return true;
    }
  }

  /**
   * Insert item x into the priority queue; allows duplicates.
   */
  /* Change c: change return type to bool */
  bool insert(Comparable &&x)
  {
    if (positions_table_.Contains(x)) // x found, no insertion
    {
      return false;
    }
    else // x not found, insert x
    {
      BinomialQueue oneItem{std::move(x)};
      // perform insertion
      positions_table_.Insert(std::move(x), oneItem.theTrees[0]); // params are key, value
      merge(oneItem);
      return true;
    }
  }

  /**
   * return true if x in positions_table_, false otherwise
   */
  /* Change d: implemented find function */
  bool Find(const Comparable &x) const
  {
    if (positions_table_.Contains(x)) // x was found
    {
      return true;
    }
    else // x was not found
    {
      return false;
    }
  }

  /**
   * checks if x in positions_table_
   * if x is present, removes x from BinomialQueue and HashTable
   * if x is not present, returns false
   */
  /* Change e: implemented remove function */
  bool Remove(const Comparable &x)
  {
    if (positions_table_.Contains(x)) // x found, removal needed
    {
      positions_table_.Remove(x); // remove x
      return true;
    }
    else // x not found, no removal
    {
      return false;
    }
  }
  /**
   * checks if x in positions_table_
   * if x is present, return false
   * if not,
   */
  /* Part 3: implementing insert for one item insertion */
  bool insertNoMerge(const Comparable &x)
  {
    if (positions_table_.Contains(x)) // x found, no insertion
    {
      return false;
    }
    else // x not found, perform insertion
    {
      // Initialize tempNode for insertion
      BinomialNode *tempNode = new BinomialNode{x, nullptr, nullptr};

      // Get first empty slot in vector of trees
      size_t emptySlot = getEmptySlot();

      // Insert the new tree into the empty slot or combine existing tree
      BinomialNode *combinedTree = tempNode;
      while (theTrees[emptySlot] != nullptr) // makes sure to leave empty slot for tempNode
      {
        //
        combinedTree = combineTrees(theTrees[emptySlot], combinedTree); // Combine trees
        theTrees[emptySlot] = nullptr;                                  // Keep empty slot empty
        ++emptySlot;                                                    // Move onto next
      }

      // Add the combined tree into the vector of trees
      theTrees[emptySlot] = combinedTree;

      // Insert to positions_table_, increment currentSize to reflect insertion
      positions_table_.Insert(x, tempNode);
      ++currentSize;
      return true;
    }
  }

  /**
   * Finds the first empty slot in the vector of trees,
   * if none found, resizes vector and makes empty slot
   * Helper function for insertNoMerge
   */
  size_t getEmptySlot()
  {
    // Look for the first empty slot in the vector of trees
    for (size_t position = 0; position < theTrees.size(); ++position)
    {
      if (theTrees[position] == nullptr)
      {
        return position;
      }
    }
    // If no empty slot is found, resize vector to make empty slot, return this position
    theTrees.resize(theTrees.size() + 1);
    return theTrees.size() - 1;
  }

  /**
   * Remove the smallest item from the priority queue.
   * Throws UnderflowException if empty.
   */
  void deleteMin()
  {
    Comparable x;
    deleteMin(x);
  }

  /**
   * Remove the minimum item and place it in minItem.
   * Throws UnderflowException if empty.
   */
  void deleteMin(Comparable &minItem)
  {
    if (isEmpty())
      throw UnderflowException{};

    int minIndex = findMinIndex();
    minItem = theTrees[minIndex]->element;

    BinomialNode *oldRoot = theTrees[minIndex];
    BinomialNode *deletedTree = oldRoot->leftChild;
    delete oldRoot;

    // Construct H''
    BinomialQueue deletedQueue;
    deletedQueue.theTrees.resize(minIndex);
    deletedQueue.currentSize = (1 << minIndex) - 1;
    for (int j = minIndex - 1; j >= 0; --j)
    {
      deletedQueue.theTrees[j] = deletedTree;
      deletedTree = deletedTree->nextSibling;
      /* Change f: track and change parent pointer, where needed */
      deletedQueue.theTrees[j]->parent = nullptr;
      deletedQueue.theTrees[j]->nextSibling = nullptr;
    }

    // Construct H'
    theTrees[minIndex] = nullptr;
    currentSize -= deletedQueue.currentSize + 1;

    merge(deletedQueue);
  }

  /**
   * Make the priority queue logically empty.
   */
  void makeEmpty()
  {
    currentSize = 0;
    for (auto &root : theTrees)
      makeEmpty(root);
  }

  /**
   * Merge rhs into the priority queue.
   * rhs becomes empty. rhs must be different from this.
   * Exercise 6.35 needed to make this operation more efficient.
   */
  void merge(BinomialQueue &rhs)
  {
    if (this == &rhs) // Avoid aliasing problems
      return;

    currentSize += rhs.currentSize;

    if (currentSize > capacity())
    {
      int oldNumTrees = theTrees.size();
      int newNumTrees = max(theTrees.size(), rhs.theTrees.size()) + 1;
      theTrees.resize(newNumTrees);
      for (int i = oldNumTrees; i < newNumTrees; ++i)
        theTrees[i] = nullptr;
    }

    BinomialNode *carry = nullptr;
    for (int i = 0, j = 1; j <= currentSize; ++i, j *= 2)
    {
      BinomialNode *t1 = theTrees[i];
      BinomialNode *t2 = i < rhs.theTrees.size() ? rhs.theTrees[i] : nullptr;

      int whichCase = t1 == nullptr ? 0 : 1;
      whichCase += t2 == nullptr ? 0 : 2;
      whichCase += carry == nullptr ? 0 : 4;

      switch (whichCase)
      {
      case 0: /* No trees */
      case 1: /* Only this */
        break;
      case 2: /* Only rhs */
        theTrees[i] = t2;
        rhs.theTrees[i] = nullptr;
        break;
      case 4: /* Only carry */
        theTrees[i] = carry;
        carry = nullptr;
        break;
      case 3: /* this and rhs */
        carry = combineTrees(t1, t2);
        theTrees[i] = rhs.theTrees[i] = nullptr;
        break;
      case 5: /* this and carry */
        carry = combineTrees(t1, carry);
        theTrees[i] = nullptr;
        break;
      case 6: /* rhs and carry */
        carry = combineTrees(t2, carry);
        rhs.theTrees[i] = nullptr;
        break;
      case 7: /* All three */
        theTrees[i] = carry;
        carry = combineTrees(t1, t2);
        rhs.theTrees[i] = nullptr;
        break;
      }
    }

    for (auto &root : rhs.theTrees)
      root = nullptr;
    rhs.currentSize = 0;
  }

private:
  struct BinomialNode
  {
    Comparable element;
    /* Change b: added parent pointer to the struct */
    BinomialNode *parent;
    BinomialNode *leftChild;
    BinomialNode *nextSibling;

    BinomialNode(const Comparable &e, BinomialNode *lt, BinomialNode *rt)
        : element{e}, leftChild{lt}, nextSibling{rt} {}

    BinomialNode(Comparable &&e, BinomialNode *lt, BinomialNode *rt)
        : element{std::move(e)}, leftChild{lt}, nextSibling{rt} {}
  };

  const static int DEFAULT_TREES = 1;

  /* Change a: add HashTable as private member */
  HashTable<Comparable, BinomialNode *> positions_table_;
  vector<BinomialNode *> theTrees; // An array of tree roots
  int currentSize;                 // Number of items in the priority queue

  /**
   * Find index of tree containing the smallest item in the priority queue.
   * The priority queue must not be empty.
   * Return the index of tree containing the smallest item.
   */
  int findMinIndex() const
  {
    int i;
    int minIndex;

    for (i = 0; theTrees[i] == nullptr; ++i)
      ;

    for (minIndex = i; i < theTrees.size(); ++i)
      if (theTrees[i] != nullptr &&
          theTrees[i]->element < theTrees[minIndex]->element)
        minIndex = i;

    return minIndex;
  }

  /**
   * Return the capacity.
   */
  int capacity() const
  {
    return (1 << theTrees.size()) - 1;
  }

  /**
   * Return the result of merging equal-sized t1 and t2.
   */
  BinomialNode *combineTrees(BinomialNode *t1, BinomialNode *t2)
  {
    if (t2->element < t1->element)
      return combineTrees(t2, t1);
    t2->nextSibling = t1->leftChild;
    t1->leftChild = t2;
    /* Change f: track and change parent pointer, where needed */
    t2->parent = t1;

    return t1;
  }

  /**
   * Make a binomial tree logically empty, and free memory.
   */
  void makeEmpty(BinomialNode *&t)
  {
    if (t != nullptr)
    {
      makeEmpty(t->leftChild);
      makeEmpty(t->nextSibling);
      delete t;
      t = nullptr;
    }
  }

  /**
   * Internal method to clone subtree.
   */
  BinomialNode *clone(BinomialNode *t) const
  {
    if (t == nullptr)
      return nullptr;
    else
      return new BinomialNode{t->element, clone(t->leftChild), clone(t->nextSibling)};
  }
};

#endif
