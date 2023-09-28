/*
Author: James Michael Crespo
File Name: Promotional.cpp
Date of Creation: 10/12/2022

Description: This file contains the implementation of the 'Promotional' class,
             a subclass of the 'Post'('Promotional' inherits from 'Post' it's public members).
*/

#include "Promotional.hpp"

/**
    Parameterized constructor.
    @param       : The name of the Promotional post (a string)
    @param       : The body of the Promotional post (a string)
    @param       : The username of the Account that added this post (a string)
    @param       : The link of the Promotional post (a string)

    @post        : Sets the title, body, username and link (if it's a proper link otherwise "Broken Link")
                   of the Promotional to the value
                   of the parameters.
                   It will also generate the current time and store it.
*/
Promotional::Promotional(std::string name, std::string body, std::string username, std::string link) : Post(name, body, username)
{
    setLink(link);
}

/**
    Accessor function
    @return      : Returns the post link
*/
std::string Promotional::getLink() const
{
    return url_;
}

/**
    @param       : A reference to the link that is in the format 'https://www.something.something'
                   or 'http://www.something.something' with the last 'something' being at least 2 characters
    @return      : true if the link is correctly formatted, false otherwise

    @post        : If the link is not correctly formatted, store "Broken Link"
                   in the link member variable, otherwise store the value of the
                   parameter (Hint: see <regex>)
*/
bool Promotional::setLink(const std::string &link)
{
    // THIS IS A REGEX PATTERN FROM 'geeksforgeeks.org'
    // the pattern is as follows:
    // ---------------------------------------------------------
    // the URL must start with either http or https and
    // then followed by :// and
    // then it must contain www. and
    // then followed by subdomain length of length (2,256) and
    // last part contains top level domain like .com, .org etc.

    std::regex format("((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
    if (std::regex_match(link, format) == true)
    {
        url_ = link;
        return true;
    }
    else
    {
        url_ = "Broken Link";
        return false;
    }
}

/**
    @post        : displays the entire Promotional post (example):
                   \n
                   {post_title_} at {time_stamp_}:
                   {post_body_}
                   \n
                   {link}
                   \n
*/
void Promotional::displayPost() const
{
    std::cout << '\n'
              << getTitle() << " at ";
    getTimeStamp();
    std::cout << getBody() << std::endl;
    std::cout << getLink() << std::endl;
}