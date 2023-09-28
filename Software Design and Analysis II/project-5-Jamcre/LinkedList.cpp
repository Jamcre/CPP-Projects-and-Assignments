/****************************************************************************************************************************
Title         :   LinkedList.hpp
Author        :   Dream Team
Description   :   Implementation files for LinkedList class
****************************************************************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>

/* Default constructor*/
template <typename ItemType>
LinkedList<ItemType>::LinkedList()
{
    head_ = nullptr;
    size_ = 0;
}

/* Copy Contructors*/
template <typename ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType> &list) // : head_{nullptr}, size_{0}
{
    head_ = nullptr;
    size_ = 0;
    if (!list.isEmpty())
    {
        Node<ItemType> *copyHead = list.getHeadPtr();
        int counter = 0;

        while (counter < list.getSize())
        {
            insert(copyHead->getItem(), counter);
            counter++;
            copyHead = copyHead->getNext();
        }
    }
}

template <typename ItemType>
Node<ItemType> *LinkedList<ItemType>::getHeadPtr() const
{
    return head_;
}

/*

    @post    : removes all items from the caller list,
               no nodes remain in the list
**/
template <typename ItemType>
void LinkedList<ItemType>::clear()
{
    Node<ItemType> *curr_item = head_;
    Node<ItemType> *temp = curr_item;
    for (int i = 0; i < size_; i++)
    {
        temp = curr_item;
        curr_item = curr_item->getNext();
        delete temp;
    }
    temp = nullptr;
    size_ = 0;
}

/* Destructor */
template <typename ItemType>
LinkedList<ItemType>::~LinkedList()
{
    clear();
}

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

template <typename ItemType>
bool LinkedList<ItemType>::remove(const int &position)
{
    if (position < 0 || position >= size_)
    {
        return false;
    }

    Node<ItemType> *iterator = nullptr;
    Node<ItemType> *previous = nullptr;

    if (position == 0)
    {
        iterator = head_;
        head_ = head_->getNext();
    }
    else
    {
        previous = getAtPos(position - 1);
        iterator = getAtPos(position);
        previous->setNext(iterator->getNext());
    }

    size_--;
    previous = nullptr;
    iterator->setNext(nullptr);
    delete iterator;
    return true;
}

/*
    @param            :   Another LinkedList passed by reference
    @post             :   Sets the current LinkedList with the same items as the provided
                          LinkedList but in reverse order
*/
template <typename ItemType>
void LinkedList<ItemType>::reverseCopy(const LinkedList<ItemType> &a_list)
{
    LinkedList<ItemType> newList(a_list);

    Node<ItemType> *current = newList.getHeadPtr();
    const int START = 0;
    const int END = newList.getSize();

    while (current != nullptr)
    {
        insert(current->getItem(), START);
        current = current->getNext();
        remove(END);
    }
}

template <typename ItemType>
int LinkedList<ItemType>::getSize() const
{
    return size_;
}

template <typename ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
    return size_ == 0 ? true : false;
}

/*
    @pre      :   current_position and new_position is valid
    @return   :   true if item is moved to new_position, false otherwise
    @post     :   Moves item from current_position to new_position, if valid
**/
template <typename ItemType>
bool LinkedList<ItemType>::moveItem(int &current_position, const int &new_position)
{
    if (
        (current_position > -1 && current_position < size_) &&
        (new_position > -1 && new_position < size_))
    {
        if (new_position != current_position)
        {
            if (new_position < current_position)
            {
                Node<ItemType> *temp_curr = this->getAtPos(current_position);
                Node<ItemType> *temp_prev = this->getAtPos(current_position - 1);
                temp_curr = temp_prev;
                temp_prev = temp_curr;
                current_position--;
            }
            else
            {
                Node<ItemType> *temp_curr = this->getAtPos(current_position);
                Node<ItemType> *temp_next = this->getAtPos(current_position + 1);
                temp_curr = temp_next;
                temp_next = temp_curr;
                current_position++;
            }

            return moveItem(current_position, new_position);
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
}

/*
    @param            :   A reference to an item
    @return           :   Return true if item was moved to top, false otherwise
    @post             :   Will move the item from its current position to the front
                          of the list.
                          For example, given the list 1 -> 3 -> 5 -> 6, moving 5 to the
                          top of the list would result in 5 -> 1 -> 3 -> 6
                          (recall that positions start at 0 and end at n-1).
*/
template <typename ItemType>
bool LinkedList<ItemType>::moveItemToTop(const ItemType &item)
{
    if (getIndexOf(item) < 1) // If the item does not exist or it is already on top, return false
        return false;
    else
    {
        Node<ItemType> *new_head = new Node<ItemType>(); // Create a new head Node
        new_head->setItem(item);                         // Set the value of the new head Node to the item you want to move
        remove(getIndexOf(item));                        // Remove the item you want to move from the List
        new_head->setNext(head_);                        // Set the new head pointer's next value to the current head pointer
        head_ = new_head;                                // Set the List's head to the new head pointer
        return true;
    }
}

/*
    @pre      :  pos is a valid place in the list, otherwise nullptr will be returned
    @param    :  the position of the item to be returned
    @return   :  a pointer to the node at pos
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

/*
    @param         : item object to find in the list
    @return     : the position (index) of the parameter object
*/
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

/**
    @param            :   pointer to primary node
    @param            :   pointer to secondary node
    @post             :   will swap the items of the 2 parameter nodes
*/
template <typename ItemType>
void LinkedList<ItemType>::swapNodeItem(Node<ItemType> *node1, Node<ItemType> *node2)
{
    Node<ItemType> *temp = nullptr;   // create temp node;
    temp->setItem(node1->getItem());  // set temp node item = node1 item
    node1->setItem(node2->getItem()); // set node1 item = node2 item
    node2->setItem(temp->getItem());  // set node2 item = temp item (really node1's item)
}

/*
 @param            :   The Comparator to sort with
 @param            :   A POINTER to an integer counter that gets incremented every time a SWAP between two Nodes occurs
                       (this is for testing purposes).
                       IT IS IMPORTANT TO PASS OUR GRADESCOPE TESTS TAHT EACH
                       TIME BUBBLE SORT MAKES A SWAP YOU INCREMENT THIS COUNTER.
 @post             :   will use Bubble Sort to order the LinkedList based on comparator
*/
template <typename ItemType>
template <typename Comparator>
void LinkedList<ItemType>::bubbleSort(Comparator compare, int *swap_count)
{
    int size = getSize() - 1;
    bool swapped = true;
    int pass = 1;
    Post *post1, *post2;
    while (swapped && (pass < size))
    {
        swapped = false;
        int index = 0;
        Node<Post *> *temp = getHeadPtr();
        while (index < size - pass)
        {
            post1 = temp->getItem();
            post2 = temp->getNext()->getItem();
            if (compare(*post2, *post1))
            {
                swapNodeItem(temp, temp->getNext());
                swapped = true;
                *swap_count++;
            }
            temp = temp->getNext();
            index++;
        }
        pass++;
    } // end while

    // Node<Post *> *temp = getHeadPtr();    // create temp pointer to head of linkedlist
    // int target_swaps = getSize() - 1;     // number of swaps required for sorted linkedlist
    // int current_swaps = 0;                // number of swaps the current pass is at
    // while (current_swaps != target_swaps) // true until linkedlist is sorted
    // {
    //     current_swaps = 0;
    //     while (temp->getNext() != nullptr)
    //     {
    //         Post *post1 = temp->getItem();
    //         Post *post2 = temp->getNext()->getItem();
    //         if (compare(*post2, *post1)) // check if bubble sort is needed
    //         {
    //             swapNodeItem(temp, temp->getNext()); // swap items to sort linkedlist
    //             *swap_count++;                       // increment total swap counter
    //             current_swaps++;                     // increment current swaps for this pass of bubble sort
    //         }
    //         temp = temp->getNext(); // move onto next node of linkedlist
    //     }
    // }
}
