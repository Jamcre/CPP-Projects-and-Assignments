/*
Author: James Michael Crespo
File Name: Network.hpp
Date of Creation: 10/12/2022

Description: This file contains the interface of the 'Network' template class.
*/

#ifndef NETWORK_H_
#define NETWORK_H_
#include "Post.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <regex>

template <class ItemType>
class Network
{
public:
  /**
     Default constructor.

     Initializes private variables to default initial values.
  */
  Network();

  /**
    Accessor function
    @return           : int -  the current size of the network (number of items in the array)
  */
  int getSizeOfNetwork() const;

  /**
    @return           : bool -  true if the bag is empty, false otherwise
  */
  bool isEmpty() const;

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
  bool addAccount(ItemType *new_item);

  /**
  Mutator function
  @param            :   a POINTER to the item that will be removed from Network
  @return           :   true if if the item was successfully removed, false otherwise
  @post             :   updates the bag/network to remove the pointer, if a pointer to that item was found.
  */
  bool removeAccount(const ItemType *old_item);

  /**
  Mutator function
  @post             :   Empties the bag/network
  */
  void clear();

  /**
  @param            :   a POINTER to the item to find
  @return           :   true if the item was successfully found, false otherwise
  */
  bool containsAccount(const ItemType *item) const;

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
  void populateNetwork(const std::string text_file);

  /**
  Mutator function
  @param            :   a reference to another Network

  @post             :  Removes from the Network any items that also appear in the other Network.
                       In other words, removes elements from the network on the left of the operator that
                       are also found in the network on the right of the operator.
  Why is this useful? For example, given a network of known bot accounts, remove all bots from this Network.
  */
  void operator-=(Network<ItemType> &item);

  /**
  Accessor function
  @param            :   a reference to the item whose feed will be displayed
  @post             :   prints the feed of the given account by checking who they are following
                        and displaying all the posts from the feed that were made by those accounts.
                        Keep in mind that the Network parameters are general template types
                        in this project rather than accounts, although this functionality is
                        specific to accounts.
  */
  void printFeedForAccount(const ItemType &item);

  /**
  @param            :   a reference to an item (account) and the username of the account
                        it wants to follow
  @return           :   true if the item was authorized to follow, false otherwise

  @post             :   the referenced Account follows another account with the username
                        specified by the second argument if they both exist in the network
  */
  bool authenticateFollow(ItemType &account, std::string username); // WIP

  /**
  Mutator function
  @param            :   a reference to a Post be added to the feed
  @return           :   returns true if the Post was successfully added to the feed, false otherwise
  @post             :   Adds the post to its feed only if the Post was created by an Account
                        in this Network.
  */
  bool addToFeed(const Post &post);

private:
  /**
  private function
  @param            :   string - the username of item we want the index of
  @return           :   int - the index of the item, -1 if the account is not found
  */
  int getIndexOf(const std::string &username) const;

  ItemType *ptr_to_accounts_[200]; // An array(capacity of 200) that stores POINTERS to template objects
  int num_of_accounts_;            // A count of the current number of accounts in the network
  std::vector<Post> network_feed_; // A vector of posts: network feed where all posts posted by accounts in network will be stored
};

#include "Network.cpp"
#endif