/*
Author: James Michael Crespo
File Name: Account.cpp
Date of Creation: 10/12/2022

Description: This file contains the implementation of the 'Account' class.
*/

#include "Account.hpp"

/**
    Default constructor.
    Sets the username and password of the Account to an empty string
    Sets the vector of posts to an empty vector
*/
Account::Account()
{
    setUsername("");
    setPassword("");
    posts_.clear();
}

/**
    Parameterized constructor.
    @param username  : username of the Account
    @param password  : password of the Account

    Sets the username and password of the Account to what was passed by the user
    Sets the vector of posts to an empty vector
*/
Account::Account(std::string username, std::string password)
{
    setUsername(username);
    setPassword(password);
    posts_.clear();
}

/**
    Mutator Function
    @param a reference to the username of the Account
*/
void Account::setUsername(const std::string &username)
{
    username_ = username;
}

/**
    Accessor Function
    @return the username of the Account
*/
std::string Account::getUsername() const
{
    return username_;
}

/**
    Mutator Function
    @param a reference to the password of the Account
*/
void Account::setPassword(const std::string &password)
{
    password_ = password;
}

/**
    Accessor Function
    @return the password of the Account
*/
std::string Account::getPassword() const
{
    return password_;
}

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
bool Account::addPost(const std::string &title, const std::string &body)
{
    if (title == "" && body == "")
    {
        return false;
    }
    else
    {
        Post new_post(title, body, username_);
        posts_.push_back(new_post);
        if (pointed_network_ != nullptr)
        {
            pointed_network_->addToFeed(new_post);
        }
        return true;
    }
}

/*
    @post         : Prints the vector of Posts using their display function
*/
void Account::viewPosts() const
{
    for (int i = 0; i < posts_.size(); i++)
    {
        posts_[i].displayPost();
    }
}

/**
  Accessor function
  @return           :   the pointer to the Network the account is in
*/
Network<Account> *Account::getNetwork() const
{
    return pointed_network_;
}

/**
  Mutator function
  @param            :   a pointer to a Network
  @post             :   the Network pointer private member points to the input Network
*/
void Account::setNetwork(Network<Account> *ptr_to_network)
{
    pointed_network_ = ptr_to_network;
}

/**
  @param            :   the username of the Account to follow
  @return           :   true if the account was successfully able to follow, false otherwise
  @post             :   adds the username to the vector of following accounts only if
                        it is affiliated to a Network AND it is not already following an account
                        with the same username.
*/
bool Account::followAccount(const std::string username)
{
    if (usernames_following_.size() == 0 && pointed_network_ != nullptr)
    {
        usernames_following_.push_back(username);
        return true;
    }
    else if (usernames_following_.size() > 0 && pointed_network_ != nullptr)
    {
        for (int i = 0; i < usernames_following_.size(); i++)
        {
            if (usernames_following_[i] == username)
            {
                return false;
            }
        }
        usernames_following_.push_back(username);
        return true;
    }
    else
    {
        return false;
    }
}

/**
  @return           :   the vector of usernames the Account is following
*/
std::vector<std::string> Account::viewFollowing() const
{
    return usernames_following_;
}