#ifndef HOMEWORK2_BINARY_SEARCH_TREE_H_
#define HOMEWORK2_BINARY_SEARCH_TREE_H_

#include "dsexceptions.h"
#include <iostream>
#include <algorithm>

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
public:
    // Part 2a Functions

    // Takes SeqMap and RecoSeq, returns matching EnzAcro, once found if it exists in tree
    Comparable &getEnzAcro(const Comparable &x)
    {
        return getEnzAcro(x, root)->element;
    }

    // End Part 2a Functions

    // Part 2b Functions

    // Traverses tree, while counting nodes, returns total node count
    int getNodeCount()
    {
        return getNodeCount(root);
    }

    // Traverses tree, while counting depth at each node, returns total depth of all nodes
    int getDepthTotal()
    {
        return getDepthTotal(root, 0);
    }

    // Counts number of times contains() is called, returns that value
    int getContainsCalls(const Comparable &x)
    {
        return getContainsCalls(root, x, 0);
    }
    // End Part 2b Functions

    BinarySearchTree() : root{nullptr} {}

    /**
     * Copy constructor
     */
    BinarySearchTree(const BinarySearchTree &rhs) : root{nullptr} { root = clone(rhs.root); }

    /**
     * Move constructor
     */
    BinarySearchTree(BinarySearchTree &&rhs) : root{rhs.root} { rhs.root = nullptr; }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree()
    {
        makeEmpty();
    }

    /**
     * Copy assignment
     */
    BinarySearchTree &operator=(const BinarySearchTree &rhs)
    {
        BinarySearchTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    /**
     * Move assignment
     */
    BinarySearchTree &operator=(BinarySearchTree &&rhs)
    {
        std::swap(root, rhs.root);
        return *this;
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMin() const
    {
        if (isEmpty())
            throw UnderflowException{};
        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMax() const
    {
        if (isEmpty())
            throw UnderflowException{};
        return findMax(root)->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const
    {
        return contains(x, root);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree() const
    {
        if (isEmpty())
            std::cout << "Empty tree" << std::endl;
        else
            printTree(root);
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x)
    {
        insert(x, root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(Comparable &&x)
    {
        insert(std::move(x), root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable &x)
    {
        remove(x, root);
    }

private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
            : element{theElement}, left{lt}, right{rt} {}

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
            : element{std::move(theElement)}, left{lt}, right{rt} {}
    };

    BinaryNode *root;

    // Part 2a Functions

    // Takes SeqMap and RecoSeq, returns matching EnzAcro, once found if it exists in tree
    BinaryNode *getEnzAcro(const Comparable &x, BinaryNode *t)
    {
        if (t == nullptr) // No SeqMap in Node, No Match
        {
            return nullptr;
        }
        else if (t->element < x) // No RecoSeq Match, go right
        {
            return getEnzAcro(x, t->right);
        }
        else if (x < t->element) // No RecoSeq Match, go left
        {
            return getEnzAcro(x, t->left);
        }
        else // Final Case, RecoSeq Match Found, Return EnzAcro
        {
            return t;
        }
    }
    // End Part 2a Functions

    // Part 2b Functions

    // Traverses tree, while counting nodes, returns total node count
    int getNodeCount(BinaryNode *t)
    {
        if (t == nullptr) // Case: No node present
        {
            return 0;
        }
        else // Case: Node present, add 1 to total, check child nodes
        {
            return 1 + getNodeCount(t->left) + getNodeCount(t->right);
        }
    }

    // Traverses tree, while counting depth at each node, returns total depth of all nodes
    int getDepthTotal(BinaryNode *t, int depth)
    {
        if (t == NULL) // Case: Node has no children, 0 depth
        {
            return 0;
        }
        else // Case: Node had children, add 1 to depth, check child nodes
        {
            return depth + getDepthTotal(t->left, depth + 1) + getDepthTotal(t->right, depth + 1);
        }
    }

    // Counts number of times contains() is called, returns that value
    int getContainsCalls(BinaryNode *t, const Comparable &x, int count)
    {
        if (t == nullptr) // Case: Node has no children, return count
        {
            return count;
        }
        else if (t->element < x) // Case: gets contains count on left child
        {
            return getContainsCalls(t->right, x, count + 1);
        }
        else if (t->element > x) // Case: gets contains count on right child
        {
            return getContainsCalls(t->left, x, count + 1);
        }
        else // Case: contains is true, return contain count.
        {
            return count;
        }
    }
    // End Part 2b Functions

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable &x, BinaryNode *&t)
    {
        if (t == nullptr)
            t = new BinaryNode{x, nullptr, nullptr};
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else // Case where Duplicate reco_seq
            t->element.Merge(x);
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(Comparable &&x, BinaryNode *&t)
    {
        if (t == nullptr)
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        else if (x < t->element)
            insert(std::move(x), t->left);
        else if (t->element < x)
            insert(std::move(x), t->right);
        else // Case where Duplicate reco_seq
            t->element.Merge(std::move(x));
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const Comparable &x, BinaryNode *&t)
    {
        if (t == nullptr)
            return; // Item not found; do nothing
        if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) // Two children
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode *findMin(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode *findMax(BinaryNode *t) const
    {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains(const Comparable &x, BinaryNode *t) const
    {
        if (t == nullptr)
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
            return true; // Match
    }
    /****** NONRECURSIVE VERSION*************************
        bool contains( const Comparable & x, BinaryNode *t ) const
        {
            while( t != nullptr )
                if( x < t->element )
                    t = t->left;
                else if( t->element < x )
                    t = t->right;
                else
                    return true;    // Match

            return false;   // No match
        }
    *****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(BinaryNode *&t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree(BinaryNode *t) const
    {
        if (t != nullptr)
        {
            printTree(t->left);
            std::cout << t->element << std::endl;
            printTree(t->right);
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode *clone(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
};

#endif // HOMEWORK2_BINARY_SEARCH_TREE_H_
