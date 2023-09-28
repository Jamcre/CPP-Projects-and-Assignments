/*
Author: James Michael Crespo
File Name: Account.hpp
Date of Creation: 08/30/2022

Description: This file contains the interface of the 'Account' class.
*/

#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "Post.hpp"

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
    @param title   : A reference to the title used to generate the Post object
    @param body    : A reference to the body used to generate the Post object
    @post         : generates a Post with the given title and body and adds it to it's vector of posts
    @return       : Will return true if the Post does not have an empty title or body and the Post is successfully added to the vector
    */
    bool addPost(const std::string &title, const std::string &body);

    /*
    @post         : Prints the vector of Posts using their display function
    */
    void viewPosts() const;

private:
    std::string username_;
    std::string password_;
    std::vector<Post> posts_;
};

#endif