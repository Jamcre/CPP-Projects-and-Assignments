/*
Author: James Michael Crespo
File Name: General.hpp
Date of Creation: 10/12/2022

Description: This file contains the interface of the 'General' class, a subclass of the 'Post'
             ('General' inherits from 'Post' it's public members).
*/

#ifndef GENERAL_H
#define GENERAL_H

#include "Post.hpp"
#include <iostream>

enum Reactions
{
    LIKE,
    DISLIKE,
    LAUGH,
    WOW,
    SAD,
    ANGRY
};

class General : public Post
{
public:
    /**
    Parameterized constructor.
    @param    : The name of the General post (a string)
    @param    : The body of the General post (a string)
    @param    : the username of the Account that added this post (a string)

    @post     : Sets the title, body, and username of the General post to the parameters.
                It will also generate the current time and store it
                and it initializes the array with default values
    */
    General(std::string name, std::string body, std::string username);

    /**
    Mutator function to add a reaction
    @param    : A reference to reaction (represented by a value of type Reaction)
    @return   : return True if the react to the post is successful or false
                if the reaction provided is not within a valid Reaction value.

    @post     : Increments the array at the index corresponding to the input Reaction
    */
    bool reactToPost(const Reactions &reaction);

    /**
    @post     : Prints the reaction to the post in this format (example):
                Like : 2 | Dislike : 0 | Laugh : 4 | Wow : 2 | Sad : 1 |  Angry : 5
    */
    void getReactions() const;

    /**
    @post     : Displays the General post (example):
                \n
                {post_title_} at {time_stamp_}:
                {post_body_}
                \n
                Like : 2 | Dislike : 0 | Laugh : 4 | Wow : 2 | Sad : 1 |  Angry : 5
                \n
    */
    void displayPost() const override;

private:
    int number_of_reactions_[6];
};

#endif