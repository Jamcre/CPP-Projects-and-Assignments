/*
Author: James Michael Crespo
File Name: Poll.cpp
Date of Creation: 10/12/2022

Description: This file contains the implementation of the 'Poll' class,
             a subclass of the 'Post'('Poll' inherits from 'Post' it's public members).
*/

#include "Poll.hpp"

/**
    Parameterized constructor.
    @param    : The title (name) of the Poll post (a string)
    @param    : The question (body) of the Poll post (a string)
    @param    : The username of the Account that added this poll (a string)
    @param    : A vector of options for the Poll post

    @post     : Sets the title, body and username of the Poll post to the value of the parameters.
                It will also generate the current time and store it and will initialize
                the vectors of options and their respective number of votes.
*/
Poll::Poll(std::string name, std::string body, std::string username, std::vector<std::string> options) : Post(name, body, username)
{
    poll_options_ = options;
    for (size_t i = 0; i < poll_options_.size(); i++)
    {
        number_of_votes_.push_back(0);
    }
}

/**

    @param    : a reference to int between 0 < number of options
    @return   : True if index is within range and we can vote for a poll,
                false otherwise
    @post     : Increments the poll votes based on the index which
                will refer to the index in the poll options
*/
bool Poll::votePoll(const int &option_num)
{
    if (option_num >= 0 && option_num < poll_options_.size())
    {
        number_of_votes_[option_num] += 1;
        return true;
    }
    return false;
}

/**
    Mutator function used to either add a poll or change one of the poll options
    @param    : A reference to the new poll option
    @param    : A reference to int that can either represent the index of the
                existing option that will be replaced
                or if choice_number > current number of options,
                it will add this new option to the poll.

    @post     : Resets the number of votes for this option.
*/
void Poll::changePollOption(const std::string &new_poll_option, const int &option_num)
{
    if (option_num < poll_options_.size())
    {
        poll_options_[option_num] = new_poll_option;
        number_of_votes_[option_num] = 0;
    }
    else
    {
        poll_options_.push_back(new_poll_option);
        number_of_votes_.push_back(0);
    }
}

/**
    Accessor function
    @post     : prints the reaction to the post in this format
                (example where option_n is the string at position n in the poll options vector):
                0 votes for: option_1
                5 votes for: option_2
                2 votes for: option_3
                ...
*/
void Poll::getPollOptions() const
{
    for (int i = 0; i < poll_options_.size(); i++)
    {
        std::cout << std::to_string(getPollVotes(i)) << " votes for: " << poll_options_[i] << std::endl;
    }
}

/**
    Accessor function
    @param    : The index of the option
    @return   : returns the number of votes for a given option
*/
int Poll::getPollVotes(const int &poll_option) const
{
    return number_of_votes_[poll_option];
}

/**
    @post     : displays the whole Poll post (example):
                \n
                {post_title_} at {time_stamp_}:
                {post_body_}
                \n
                0 votes for: option_1
                5 votes for: option_2
                2 votes for: option_3
                ...
                \n
*/
void Poll::displayPost() const
{
    std::cout << '\n'
              << getTitle() << " at ";
    getTimeStamp();
    std::cout << getBody() << std::endl;
    getPollOptions();
};