/*
Author: James Michael Crespo
File Name: LinkedList.cpp
Date of Creation: 10/12/2022

Description: This file contains the implementation of the 'LinkedList' template class.
*/

#include <iostream>

/* Default constructor*/
template <typename ItemType>
LinkedList<ItemType>::LinkedList() : head_{nullptr}, size_{0} {}

/* Destructor */
template <typename ItemType>
LinkedList<ItemType>::~LinkedList()
{
    clear();
}

/*
    Copy constructor
    @param            :   Another LinkedList passed by reference

    Initializes this LinkedList with the same items as the provided LinkedList
*/
template <typename ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType> &another_LinkedList)
{
    size_ = another_LinkedList.getSize();
    Node<ItemType> *orig_chain_ptr = another_LinkedList.getHeadPtr(); // Point to node in original LinkedList
    if (orig_chain_ptr == nullptr)
    {
        head_ = nullptr; // Original LinkedList is empty
    }
    else
    {
        head_ = new Node<ItemType>();
        head_->setItem(orig_chain_ptr->getItem());

        // Copy remaining nodes
        Node<ItemType> *new_chain_ptr = head_;      // Points to last node in new chain
        orig_chain_ptr = orig_chain_ptr->getNext(); // Advance original-chain pointer
        while (orig_chain_ptr != nullptr)
        {
            // Get next item from original chain
            ItemType next_item = orig_chain_ptr->getItem();
            // Create a new node containing the next item
            Node<ItemType> *new_node_ptr = new Node<ItemType>(next_item);
            // Link new node to end of new chain
            new_chain_ptr->setNext(new_node_ptr);

            // Advance pointer to new last node
            new_chain_ptr = new_chain_ptr->getNext();
            // Advance original-chain pointer
            orig_chain_ptr = orig_chain_ptr->getNext();
        }
        new_chain_ptr->setNext(nullptr); // Flag end of chain
    }
}

/*
    A reversed copy function
    @param            :   Another LinkedList passed by reference

    Sets the current LinkedList with the same items as the provided LinkedList
    but in reverse order
*/
template <typename ItemType>
void LinkedList<ItemType>::reverseCopy(const LinkedList<ItemType> &another_LinkedList)
{
    LinkedList<ItemType> copy_list(another_LinkedList);
    Node<ItemType> *temp = another_LinkedList.getHeadPtr();
    while (temp != NULL)
    {
        insert(temp->getItem(), 0);
        temp = temp->getNext();
        remove(another_LinkedList.getSize());
    }
}

/* @return  : the head pointer
This function is for grading purposes*/
template <typename ItemType>
Node<ItemType> *LinkedList<ItemType>::getHeadPtr() const
{
    return head_;
}

/*
    @post   : removes all items from the caller list
**/
template <typename ItemType>
void LinkedList<ItemType>::clear()
{

    Node<ItemType> *curr_item = head_;
    while (curr_item != nullptr)
    {
        Node<ItemType> *temp = curr_item;
        curr_item = curr_item->getNext();
        // delete temp->getItem();
        // temp->setItem(NULL);
        // temp->setNext(nullptr);
        delete temp;
        temp = nullptr;
    }
}

/*
    @param  item: the item to insert in the list
    @param  position: the position where to inserted
    @pre position is a valid place within the list, otherwise false will be returned
    @return   :  true if the item has been inserted in the caller list,
                false otherwise
    @post     : Inserts item in  list at  position
**/
template <typename ItemType>
bool LinkedList<ItemType>::insert(const ItemType &item, const int &position)
{
    if ((position < 0 || position > size_))
    {
        return false;
    }

    Node<ItemType> *node = new Node<ItemType>();
    node->setItem(item);

    if (size_ == 0)
    {
        head_ = node;
    }
    else
    {
        Node<ItemType> *iterator;

        if (position == 0)
        {
            node->setNext(head_);
            head_ = node;
        }

        else if (position == size_)
        {
            iterator = getAtPos(size_ - 1);
            iterator->setNext(node);
        }
        else
        {
            iterator = getAtPos(position - 1);
            node->setNext(iterator->getNext());
            iterator->setNext(node);
        }
    }
    size_++;
    return true;
}

/*
    @param  position:  the position where to remove
    @pre position is a valid place within the list, otherwise false will be returned
    @pre      : returns true if the item at position has been removed from the list,
                false otherwise
    @post     : removes node at  position
**/
template <typename ItemType>
bool LinkedList<ItemType>::remove(const int &position)
{
    if (position < 0 || position >= size_)
    {
        return false;
    }

    Node<ItemType> *iterator;

    if (position == 0)
    {
        iterator = head_;
        head_ = head_->getNext();
    }
    else
    {
        iterator = getAtPos(position - 1);
        iterator->setNext(iterator->getNext()->getNext());
        iterator = iterator->getNext();
    }

    return true;
}

/*
    @param   item : the item to find in the list
    @pre      : takes item object and checks if exist in list and return
    @return   : returns the position (index) of object in the list
**/
template <typename ItemType>
int LinkedList<ItemType>::getIndexOf(const ItemType &item) const
{
    Node<ItemType> *curr_item = head_;
    int counter = 0;
    while (curr_item != nullptr)
    {
        if (curr_item->getItem() == item)
        {
            return counter;
        }
        counter++;
        curr_item = curr_item->getNext();
    }
    return -1;
}

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
template <typename ItemType>
bool LinkedList<ItemType>::moveItemToTop(ItemType &item) // FIX REIMPLEMENT
{
    Node<ItemType> *temp = getHeadPtr();
    while (temp->getItem() != item)
    {
        temp->getItem();
        temp = temp->getNext();
        if (temp->getItem() == item)
        {
            remove(getIndexOf(item));
            insert(item, 0);
            return true;
        }
    }
    return false;
}

/* @return  : the size of the list */
template <typename ItemType>
int LinkedList<ItemType>::getSize() const
{
    return size_;
}

/* @return  : true if the list is empty, false otherwise */
template <typename ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
    return size_ == 0 ? true : false;
}

// PRIVATE METHODS

/*
    @param   pos : the position of the item
    @pre     : pos is a valid place in the list
    @return  : a pointer to the node at pos, if pos is invalid, returns nullptr
**/
template <typename ItemType>
Node<ItemType> *LinkedList<ItemType>::getAtPos(const int &pos) const
{

    if (pos < 0 || pos >= size_)
    {
        return nullptr;
    }

    Node<ItemType> *curr_item = head_;
    int counter = 0;
    while (counter < pos && curr_item != nullptr)
    {
        counter++;
        curr_item = curr_item->getNext();
    }
    return curr_item;
}