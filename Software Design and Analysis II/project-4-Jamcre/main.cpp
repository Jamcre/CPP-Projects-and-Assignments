/*
Author: James Michael Crespo
File Name: main.cpp
Date of Creation: 10/12/2022

Description: This file contains the tests for Project 4.
*/
#include "Network.hpp"
#include "LinkedList.hpp"
#include "Account.hpp"
#include "General.hpp"
#include "Post.hpp"
#include "Poll.hpp"
#include "Promotional.hpp"
#include <iostream>
#include <vector>

int main()
{
    std::vector<std::string> poll1_options;
    poll1_options.push_back("yes");
    poll1_options.push_back("no");
    Post *ptr_general = new General("test general", "body of derived post class general", "user1");
    Post *ptr_promotional = new Promotional("test promotional", "body of derived post class promotional", "user1", "https://www.google.com");
    Post *ptr_poll = new Poll("test poll", "body of derived post class poll", "user1", poll1_options);

    Account acc1("user1", "pass1");
    if (acc1.addPost(ptr_general) && acc1.addPost(ptr_promotional) && acc1.addPost(ptr_poll))
    {
        acc1.viewPosts();
    }

    return 0;
}