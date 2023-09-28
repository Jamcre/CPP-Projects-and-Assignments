/*
Author: James Michael Crespo
File Name: Network.cpp
Date of Creation: 10/12/2022

Description: This file contains the implementation of the 'Network' template class.
*/

#include "Network.hpp"

/**
  Default constructor.

  Initializes private variables to default initial values.
*/
template <class ItemType>
Network<ItemType>::Network()
{
  num_of_accounts_ = 0;
  network_feed_.clear();
}

/**
  Accessor function
  @return           : int -  the current size of the network (number of items in the array)
*/
template <class ItemType>
int Network<ItemType>::getSizeOfNetwork() const
{
  return num_of_accounts_;
}

/**
  @return           : bool -  true if the network is empty, false otherwise
*/
template <class ItemType>
bool Network<ItemType>::isEmpty() const
{
  return num_of_accounts_ == 0;
}

/**
  @param            : a POINTER to the item that will be added to the Network
  @return           : bool- true  if the item was successfully added, false otherwise
  @post             : stores a pointer to the item, if there is room. This is a network specific function,
                      it has an additional constraint: the item will be added only if no other item in the network
                      has the same username (usernames are considered unique)
                      REMEMBER WE ARE STORING POINTERS TO ITEMS, NOT ITEMS.
                      Finally, the Account being added to the network will update it's private member to point to this network
                      (see Account class modifications below, you may come back and implement this feature after
                      you work on Task 2, but don't forget!!!).
                      NOTE: every object in C++ has access to a pointer to itself called `this`, thus the nework can pass `this` pointer to the account!
*/
template <class ItemType>
bool Network<ItemType>::addAccount(ItemType *new_item)
{
  bool has_room = (num_of_accounts_ < 200);
  if (has_room)
  {
    for (int i = 0; i < num_of_accounts_; i++)
    {
      if (ptr_to_accounts_[i]->getUsername() == new_item->getUsername())
      {
        return false;
      }
    }
    ptr_to_accounts_[num_of_accounts_] = new_item;
    ptr_to_accounts_[num_of_accounts_]->setNetwork(this);
    num_of_accounts_++;
    return true;
  }
  return false;
}

/**
  Mutator function
  @param            :   a POINTER to the item that will be removed from Network
  @return           :   true if the item was successfully removed, false otherwise
  @post             :   updates the bag/network to remove the pointer, if a pointer to that item was found.
*/
template <class ItemType>
bool Network<ItemType>::removeAccount(const ItemType *old_item)
{
  int found_index = getIndexOf(old_item->getUsername());
  bool can_remove = !isEmpty() && (found_index > -1);
  if (can_remove)
  {
    num_of_accounts_--;
    ptr_to_accounts_[found_index] = ptr_to_accounts_[num_of_accounts_];
  }
  return can_remove;
}

/**
  Mutator function
  @post             :   Empties the bag/network
*/
template <class ItemType>
void Network<ItemType>::clear()
{
  for (int i = 0; i < 200; i++)
  {
    ptr_to_accounts_[i] = nullptr;
  }
  network_feed_.clear();
  num_of_accounts_ = 0;
}

/**
  @param            :   a POINTER to the item to find
  @return           :   true if the item was successfully found, false otherwise
*/
template <class ItemType>
bool Network<ItemType>::containsAccount(const ItemType *item) const
{
  return getIndexOf(item->getUsername()) > -1;
}

/**
  Mutator function
  @param            :   the name of an input file
  @pre              :   The format of the text file is as follows:
                        username password
                        username password
                        ;

                        where ';' signals the end of the file. Check the provided example (accounts.txt).

  @post             :   Reads every line in the input file, creates an Account from that information and
                        adds the Account to the network. If a line of input is missing some required information,
                        it prints out "Improper Format" and terminates.
                        Keep in mind that, although the input will always be an Account, the Network class is
                        a template, thus it will store a pointer to a generic type. It will do so by creating a new
                        dynamic object of type ItemType but passing the account information (username and password)
                        as to the Account constructor. This is a bit hacky, but it will work for our Network.
*/
template <class ItemType>
void Network<ItemType>::populateNetwork(std::string text_file)
{
  std::string line;
  std::string space = " ";
  std::regex format(".+[ ].+");
  std::ifstream my_file(text_file);
  if (my_file.is_open())
  {
    while (getline(my_file, line))
    {
      if (std::regex_match(line, format) && line != ";")
      {
        int space_pos = line.find(space);
        std::string username = line.substr(0, space_pos);
        std::string password = line.substr(space_pos + 1, line.length());
        ItemType *ptr_account = new ItemType(username, password);
        addAccount(ptr_account);
      }
      else if (!std::regex_match(line, format) && line == ";")
      {
        my_file.close();
      }
      else
      {
        my_file.close();
        std::cout << "Improper Format" << std::endl;
      }
    }
  }
}

/**
  Mutator function
  @param            :  a reference to another Network

  @post             :  Removes from the Network any items that also appear in the other Network.
                       In other words, removes elements from the network on the left of the operator that
                       are also found in the network on the right of the operator.
  Why is this useful? For example, given a network of known bot accounts, remove all bots from this Network.
*/
template <class ItemType>
void Network<ItemType>::operator-=(Network<ItemType> &item)
{
  for (int i = 0; i < num_of_accounts_; i++)
  {
    if (item.containsAccount(ptr_to_accounts_[i]))
    {
      removeAccount(ptr_to_accounts_[i]);
    }
  }
}

/**
  Accessor function
  @param            :   a reference to the item whose feed will be displayed
  @post             :   prints the feed of the given account by checking who they are following
                        and displaying all the posts from the feed that were made by those accounts.
                        Keep in mind that the Network parameters are general template types
                        in this project rather than accounts, although this functionality is
                        specific to accounts.
*/
template <class ItemType>
void Network<ItemType>::printFeedForAccount(const ItemType &item)
{
  std::vector<std::string> following = item.viewFollowing();
  for (int i = 0; i < following.size(); i++)
  {
    for (int j = 0; j < network_feed_.size(); j++)
    {
      if (following[i] == network_feed_[j].getUsername())
      {
        network_feed_[j].displayPost();
      }
    }
  }
}

/**
  @param            :   a reference to an item (account) and the username of the account
                        it wants to follow
  @return           :   true if the item was authorized to follow, false otherwise

  @post             :   the referenced Account follows another account with the username
                        specified by the second argument if they both exist in the network
*/
template <class ItemType>
bool Network<ItemType>::authenticateFollow(ItemType &account, std::string username)
{
  if (getIndexOf(account.getUsername()) > -1 && getIndexOf(username) > -1)
  {
    account.followAccount(username);
    return true;
  }
  return false;
}

/**
  Mutator function
  @param            :   a reference to a Post be added to the feed
  @return           :   returns true if the Post was successfully added to the feed, false otherwise
  @post             :   Adds the post to its feed only if the Post was created by an Account
                        in this Network.
*/
template <class ItemType>
bool Network<ItemType>::addToFeed(const Post &post)
{
  for (int i = 0; i < num_of_accounts_; i++)
  {
    if (ptr_to_accounts_[i]->getUsername() == post.getUsername())
    {
      network_feed_.push_back(post);
      return true;
    }
  }
  return false;
}

// ********* PRIVATE METHODS **************//

/**
  A function that returns the index of a given account within the Network.
  private function
  @param            :   string - the username of item we want the index of
  @return           :   int - the index of the item, -1 if the account is not found
*/
template <class ItemType>
int Network<ItemType>::getIndexOf(const std::string &username) const
{
  bool found = false;
  int result = -1;
  int search_index = 0;

  while (!found && (search_index < num_of_accounts_))
  {
    if (ptr_to_accounts_[search_index]->getUsername() == username)
    {
      found = true;
      result = search_index;
    }
    else
    {
      search_index++;
    }
  }
  return result;
}