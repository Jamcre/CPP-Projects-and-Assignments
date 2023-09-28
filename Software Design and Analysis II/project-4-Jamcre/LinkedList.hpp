/*
Author: James Michael Crespo
File Name: LinkedList.hpp
Date of Creation: 10/12/2022

Description: This file contains the interface of the 'LinkedList' template class.
*/

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

    /* Destructor */
    ~LinkedList();

    /*
        Copy constructor
        @param            :   Another LinkedList passed by reference

        Initializes this LinkedList with the same items as the provided LinkedList
    */
    LinkedList(const LinkedList<ItemType> &another_LinkedList);

    /*
        A reversed copy function
        @param            :   Another LinkedList passed by reference

        Sets the current LinkedList with the same items as the provided LinkedList
        but in reverse order
    */
    void reverseCopy(const LinkedList<ItemType> &another_LinkedList);

    /*
        @param  item: the item to insert in the list
        @param  position: the position where to inserted
        @pre position is a valid place within the list, otherwise false will be returned
        @return   :  true if the item has been inserted in the caller list,
                    false otherwise
        @post     : Inserts item in  list at  position
    **/
    bool insert(const ItemType &item, const int &position);

    /*
        @param  position:  the position where to remove
        @pre position is a valid place within the list, otherwise false will be returned
        @pre      : returns true if the item at position has been removed from the list,
                    false otherwise
        @post     : removes node at  position
    **/
    bool remove(const int &position);

    /* @return  : the size of the list */
    int getSize() const;

    /* @return  : the head pointer
    This function is for grading purposes*/
    Node<ItemType> *getHeadPtr() const;

    /* @return  : true if the list is empty, false otherwise */
    bool isEmpty() const;

    /*
        @post   : removes all items from the caller list
    **/
    void clear();

    /*
        @param   item : the item to find in the list
        @pre      : takes item object and checks if exist in list and return
        @return   : returns the position (index) of object in the list
    **/
    int getIndexOf(const ItemType &item) const;

    /*
        @param            :   A reference to an item
        @return           :   Return true if item was moved to top, false otherwise
        @post             :   Will move the item from its current position to the front
                              of the list.
                              For example, given the list 1 -> 3 -> 5 -> 6, moving 5 to the
                              top of the list would result in 5 -> 1 -> 3 -> 6
                              (recall that positions start at 0 and end at n-1).

        You are encouraged to create your own helper functions for this endeavour.
    */
    bool moveItemToTop(ItemType &item);

private:
    /*
        @param   pos : the position of the item
        @pre     : pos is a valid place in the list
        @return  : a pointer to the node at pos, if pos is invalid, returns nullptr
    **/
    Node<ItemType> *getAtPos(const int &pos) const;
    Node<ItemType> *head_;
    size_t size_;
};

#include "LinkedList.cpp"
#endif