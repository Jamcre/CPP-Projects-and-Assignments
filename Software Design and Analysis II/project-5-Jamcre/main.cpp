/*
Author: James Michael Crespo
File Name: main.cpp
Date of Creation: 11/07/2022

Description: This file contains the tests for Project 5.
*/

#include "Account.hpp"
#include "Post.hpp"
#include "General.hpp"
#include "LinkedList.hpp"
#include "Network.hpp"
#include "Node.hpp"

#include <iostream>
#include <vector>

int main()
{

    // TASK 1 TESTS
    Post *ptr_general0 = new General("Title of general post 0", "description of general post 0", "user0");
    Post *ptr_general1 = new General("Title of general post 1", "description of general post 1", "user1");
    Post *ptr_general2 = new General("Title of general post 2", "description of general post 2", "user2");
    Post *ptr_general3 = new General("Title of general post 3", "description of general post 3", "user3");
    Post *ptr_general4 = new General("Title of general post 4", "description of general post 4", "user4");

    // // operator< test
    // if (ptr_general0->operator<(*ptr_general1))
    // {
    //     std::cout << "Worked" << std::endl;
    // }
    // else
    // {
    //     std::cout << "Didn't Work" << std::endl;
    // }

    // // operator> test
    // if (ptr_general3->operator>(*ptr_general1))
    // {
    //     std::cout << "Worked" << std::endl;
    // }
    // else
    // {
    //     std::cout << "Didn't Work" << std::endl;
    // }

    // TASK 2 TESTS

    // create network and pointer
    Network<Account> net1;

    // create accounts
    Account *ptr_user0 = new Account("user0", "pass0");
    Account *ptr_user1 = new Account("user1", "pass1");
    Account *ptr_user2 = new Account("user2", "pass2");
    Account *ptr_user3 = new Account("user3", "pass3");
    Account *ptr_user4 = new Account("user4", "pass4");

    // add accounts to network
    net1.addAccount(ptr_user0);
    net1.addAccount(ptr_user1);
    net1.addAccount(ptr_user2);
    net1.addAccount(ptr_user3);
    net1.addAccount(ptr_user4);

    // add posts to accounts
    ptr_user1->addPost(ptr_general1);
    ptr_user3->addPost(ptr_general3);
    ptr_user4->addPost(ptr_general4);
    ptr_user0->addPost(ptr_general0);
    ptr_user2->addPost(ptr_general2);

    int comparison_count = 0;                      // counter for total swaps in bubble sort
    int *ptr_comparison_count = &comparison_count; // pointer to total swap counter

    // unsorted list
    // net1.printFeed();

    // SortByUsername test (least to greatest)
    LinkedList<Post *> least_to_great = net1.bSortByUsername(std::less<Post>(), ptr_comparison_count);

    // Node<Post *> *temp1 = least_to_great.getHeadPtr();
    // std::cout << "\nSORTED FROM LEAST TO GREATEST: " << std::endl;
    // while (temp1 != nullptr)
    // {
    //     std::cout << temp1->getItem()->getUsername() << std::endl;
    //     temp1 = temp1->getNext();
    // }

    // // SortByUsername test (greatest to least)
    // LinkedList<Post *> great_to_least = net1.bSortByUsername(std::greater<Post>(), ptr_comparison_count);
    // Node<Post *> *temp2 = great_to_least.getHeadPtr();
    // std::cout << "SORTED FROM GREATEST TO LEAST " << std::endl;
    // while (temp2 != nullptr)
    // {
    //     std::cout << temp2->getItem()->getUsername() << std::endl;
    //     temp2 = temp2->getNext();
    // }

    return 0;
}