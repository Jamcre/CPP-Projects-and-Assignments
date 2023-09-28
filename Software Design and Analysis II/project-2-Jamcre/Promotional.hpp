/*
Author: James Michael Crespo
File Name: Promotional.hpp
Date of Creation: 09/19/2022

Description: This file contains the interface of the 'Promotional' class, a subclass of the 'Post'
             ('Promotional' inherits from 'Post' it's public members).
*/

#ifndef PROMOTIONAL_H
#define PROMOTIONAL_H
#include "Post.hpp"
#include <iostream>
#include <regex>

class Promotional : public Post
{
public:
    /**
    Parameterized constructor.
    @param       : The name of the Promotional post (a string)
    @param       : The body of the Promotional post (a string)
    @param       : The username of the Account that added this post (a string)
    @param       : The link of the Promotional post (a string)

    @post        : Sets the title, body, username and link (if it's a proper link otherwise "Broken Link")
                   of the Promotional to the value of the parameters.
                   It will also generate the current time and store it.
    */
    Promotional(std::string name, std::string body, std::string username, std::string link);

    /**
    Accessor function
    @return      : Returns the post link
    */
    std::string getLink() const;

    /**
    @param       : A reference to the link that is in the format 'https://www.something.something'
                   or 'http://www.something.something' with the last 'something' being at least 2 characters
    @return      : true if the link is correctly formatted, false otherwise

    @post        : If the link is not correctly formatted, store "Broken Link"
                   in the link member variable, otherwise store the value of the
                   parameter (Hint: see <regex>)
    */
    bool setLink(const std::string &link);

    /**
    @post        : displays the entire Promotional post (example):
                   \n
                   {post_title_} at {time_stamp_}:
                   {post_body_}
                   \n
                   {link}
                   \n
    */
    void displayPost() const;

private:
    std::string url_;
};

#endif
