/****************************************************************************************************************************
Title         :   LinkedList.hpp
Author        :   Dream Team
Description   :   header/interface files for LinkedList class
****************************************************************************************************************************/

#ifndef LinkedList_
#define LinkedList_

#include <iostream>
#include "Node.hpp"

template <typename ItemType>
class LinkedList
{

public:
    /* Default constructor*/
    LinkedList();

    /* Copy Contructors*/
    LinkedList(const LinkedList<ItemType> &list);

    /* Destructor */
    ~LinkedList();

    /*
        Inserts parameter item in caller list at parameter position
        @pre position is a valid place within the list, otherwise false will be returned
        @post returns true if the item has been inserted in the caller list
    **/
    bool insert(const ItemType &item, const int &position);

    /*
        removes node at parameter position
        @pre position is a valid place within the list, otherwise false will be returned
        @post returns true if the item at position has been removed from the caller list
    **/
    bool remove(const int &position);

    /* Returns the size of the lis;t */
    int getSize() const;

    /* Returns the head pointer */
    Node<ItemType> *getHeadPtr() const;

    /* Returns whether the caller list is empty */
    bool isEmpty() const;

    /*
        @post    : removes all items from the caller list,
                   no nodes remain in the list
    **/
    void clear();

    /*
        @param         : item object to find in the list
        @return     : the position (index) of the parameter object
    **/
    int getIndexOf(const ItemType &item) const;

    /*
        @pre      :   current_position and new_position is valid
        @return   :   true if item is moved to new_position, false otherwise
        @post     :   Moves item from current_position to new_position, if valid
    **/
    bool moveItem(int &current_position, const int &new_position);

    /*
        @param            :   A reference to an item
        @return           :   Return true if item was moved to top, false otherwise
        @post             :   Will move the item from its current position to the front
                              of the list.
                              For example, given the list 1 -> 3 -> 5 -> 6, moving 5 to the
                              top of the list would result in 5 -> 1 -> 3 -> 6
                              (recall that positions start at 0 and end at n-1).
    */
    bool moveItemToTop(const ItemType &item);

    /*
        @param            :   Another LinkedList passed by reference
        @post             :   Sets the current LinkedList with the same items as the provided
                              LinkedList but in reverse order
    */
    void reverseCopy(const LinkedList<ItemType> &a_list);

    /*
        @param            :   pointer to primary node
        @param            :   pointer to secondary node
        @post             :   will swap the items of the 2 parameter nodes
    */
    void swapNodeItem(Node<ItemType> *node1, Node<ItemType> *node2);

    /*
     @param            :   The Comparator to sort with
     @param            :   A POINTER to an integer counter that gets incremented every time a SWAP between two Nodes occurs
                           (this is for testing purposes).
                           IT IS IMPORTANT TO PASS OUR GRADESCOPE TESTS TAHT EACH
                           TIME BUBBLE SORT MAKES A SWAP YOU INCREMENT THIS COUNTER.
     @post             :   will use Bubble Sort to order the LinkedList based on comparator
    */
    template <typename Comparator>
    void bubbleSort(Comparator compare, int *swap_count);

private:
    /*
        @pre      :  pos is a valid place in the list, otherwise nullptr will be returned
        @param    :  the position of the item to be returned
        @return   :  a pointer to the node at pos
    **/
    Node<ItemType> *getAtPos(const int &pos) const;
    Node<ItemType> *head_;
    size_t size_;
};

#include "LinkedList.cpp"
#endif
