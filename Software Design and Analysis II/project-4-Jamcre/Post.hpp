/*
Author: James Michael Crespo
File Name: Post.hpp
Date of Creation: 09/13/2022

Description: This file contains the interface of the 'Post' class.
*/

#ifndef POST_H
#define POST_H

#include <iostream>
#include <time.h>

class Post
{
public:
    /**
    Parameterized constructor.
    @param title  : The title of the post
    @param body   : The body content of the post
    Sets the title and body of the Post to what was passed by the user
    Will also generate the current time and store it
    */
    Post(std::string title, std::string body, std::string username);

    /**
    Mutator Function
    @param  : a reference to title of the Post
    */
    void setTitle(const std::string &title);

    /**
    Accessor Function
    @return : the title of the Post
    */
    std::string getTitle() const;

    /**
    Mutator Function
    @param  : a reference to body of the Post
    */
    void setBody(const std::string &body);

    /**
    Accessor Function
    @return : the body of the Post
    */
    std::string getBody() const;

    /**
    Mutator Function
    @param        : a reference to the username associated with this Post
    */
    void setUsername(const std::string &username);

    /**
    Accessor Function
    @return       : username associated with this Post
    */
    std::string getUsername() const;

    /*
    @post         : updates the time_stamp_ to the current time
    */
    void updateTimeStamp();

    /**
    @post   : prints the time the Post was created to the standard output as asctime(localtime(&time_stamp_))
    */
    void getTimeStamp() const;

    /**
    Print the Post in the following format:
    \n
    {title} posted at {time}:
    {body}
    \n
    */
    virtual void displayPost() const = 0;

private:
    std::string title_;
    std::string body_;
    std::string username_;
    time_t time_stamp_;
};

#endif