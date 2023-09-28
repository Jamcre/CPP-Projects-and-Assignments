/*
Author: James Michael Crespo
File Name: General.cpp
Date of Creation: 09/13/2022

Description: This file contains the implementation of the 'General' class,
             a subclass of the 'Post'('General' inherits from 'Post' it's public members).
*/

#include "General.hpp"

/**
    Parameterized constructor.
    @param    : The name of the General post (a string)
    @param    : The body of the General post (a string)
    @param    : the username of the Account that added this post (a string)

    @post     : Sets the title, body, and username of the General post to the parameters.
                It will also generate the current time and store it
                and it initializes the array with default values
*/
General::General(std::string name, std::string body, std::string username) : Post(name, body, username)
{
    for (int i = 0; i < 6; i++)
    {
        number_of_reactions_[i] = 0;
    }
}

/**
    Mutator function to add a reaction
    @param    : A reference to reaction (represented by a value of type Reaction)
    @return   : return True if the react to the post is successful or false
                if the reaction provided is not within a valid Reaction value.

    @post     : Increments the array at the index corresponding to the input Reaction
*/
bool General::reactToPost(const Reactions &reaction)
{
    for (int i = 0; i < 6; i++)
    {
        if (i == reaction)
        {
            number_of_reactions_[i] = number_of_reactions_[i] + 1;
            return true;
        }
    }
    return false;
}

/**
    @post     : Prints the reaction to the post in this format (example):
                Like : 2 | Dislike : 0 | Laugh : 4 | Wow : 2 | Sad : 1 | Angry : 5
*/
void General::getReactions() const
{
    std::string reaction_line = "";
    std::string reactions[6] = {"Like", "Dislike", "Laugh", "Wow", "Sad", "Angry"};

    for (int i = 0; i < 6; i++)
    {
        reaction_line += reactions[i] + " : " + std::to_string(number_of_reactions_[i]) + " | ";
    }
    reaction_line.pop_back();
    reaction_line.pop_back();
    std::cout << reaction_line << std::endl;
}

/**
    @post     : Displays the General post (example):
                \n
                {post_title_} at {time_stamp_}:
                {post_body_}
                \n
                Like : 2 | Dislike : 0 | Laugh : 4 | Wow : 2 | Sad : 1 | Angry : 5
                \n
*/
void General::displayPost() const
{
    Post::displayPost();
    std::cout << "\n";
    getReactions();
    std::cout << "\n";
}