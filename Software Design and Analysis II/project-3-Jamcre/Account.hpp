/*
Author: James Michael Crespo
File Name: Account.hpp
Date of Creation: 10/12/2022

Description: This file contains the interface of the 'Account' class.
*/

#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "Post.hpp"
#include "Network.hpp"
#include <iostream>
#include <vector>

class Account
{

public:
  /**
  Default constructor.
  Sets the username and password of the Account to an empty string
  Sets the vector of posts to an empty vector
  */
  Account();

  /**
  Parameterized constructor.
  @param username  : username of the Account
  @param password  : password of the Account

  Sets the username and password of the Account to what was passed by the user
  Sets the vector of posts to an empty vector
  */
  Account(std::string username, std::string password);

  /**
  Mutator Function
  @param a reference to the username of the Account
  */
  void setUsername(const std::string &username);

  /**
  Accessor Function
  @return the username of the Account
  */
  std::string getUsername() const;

  /**
  Mutator Function
  @param a reference to the password of the Account
  */
  void setPassword(const std::string &password);

  /**
  Accessor Function
  @return the password of the Account
  */
  std::string getPassword() const;

  /**
     MODIFY this function to also add the Account username to the Post and then add the Post
     to its Networks feed if it is connected to one. NOTE: you will need to add this functionality
     to the network as well (see Network modifications below - you may want to create a STUB for it,
     or implement this functionality after you modified the Network.)

     @param title   : A reference to the title used to generate the Post object
     @param body    : A reference to the body used to generate the Post object
     @post          : generates a Post with the given title and body and adds it to it's vector
                      of posts AND to the Network's feed if it is connected to a Network.
     @return        : Will return true if the Post does not have an empty title or body and the
                      Post is successfully added to the vector
  */
  bool addPost(const std::string &title, const std::string &body);

  /*
  @post         : Prints the vector of Posts using their display function
  */
  void viewPosts() const;

  /**
    Accessor function
    @return           :   the pointer to the Network the account is in
  */
  Network<Account> *getNetwork() const;

  /**
    Mutator function
    @param            :   a pointer to a Network
    @post             :   the Network pointer private member points to the input Network
  */
  void setNetwork(Network<Account> *ptr_to_network);

  /**
    @param            :   the username of the Account to follow
    @return           :   true if the account was successfully able to follow, false otherwise
    @post             :   adds the username to the vector of following accounts only if
                          it is affiliated to a Network AND it is not already following an account
                          with the same username.
  */
  bool followAccount(const std::string username);

  /**
    @return           :   the vector of usernames the Account is following
  */
  std::vector<std::string> viewFollowing() const;

private:
  std::string username_;
  std::string password_;
  std::vector<Post> posts_;
  std::vector<std::string> usernames_following_;
  Network<Account> *pointed_network_ = nullptr;
};

#endif