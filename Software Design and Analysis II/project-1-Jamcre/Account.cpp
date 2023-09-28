/*
Author: James Michael Crespo
File Name: Account.cpp
Date of Creation: 08/30/2022

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
    username_ = "";
    password_ = "";
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
    username_ = username;
    password_ = password;
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
    @param title   : A reference to the title used to generate the Post object
    @param body    : A reference to the body used to generate the Post object
    @post         : generates a Post with the given title and body and adds it to it's vector of posts
    @return       : Will return true if the Post does not have an empty title or body and the Post is successfully added to the vector
*/
bool Account::addPost(const std::string &title, const std::string &body)
{
    if (title != "" && body != "")
    {
        Post newPost(title, body);
        posts_.push_back(newPost);
        return true;
    }
    else
    {
        return false;
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