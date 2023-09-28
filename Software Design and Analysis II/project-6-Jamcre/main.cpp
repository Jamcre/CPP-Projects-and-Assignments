/*
Author: James Michael Crespo
File Name: main.cpp
Date of Creation: 11/22/2022
Description: This file contains the tests for project 6.
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
    // // TASK 1 TESTS
    // Post *ptr_post0 = new General("title of general post 0", "description of general post 0", "user0");
    // std::cout << "\nTASK 1 TESTS:\n";

    // // test like()
    // ptr_post0->like();
    // std::cout << "test like(): PASSED" << std::endl;

    // // test getLikes()
    // std::cout << ptr_post0->getLikes() << " like(s)" << std::endl;
    // std::cout << "test getLikes(): PASSED" << std::endl;

    // // test setPriority()
    // ptr_post0->setPriority(ptr_post0->LOW);
    // std::cout << "test setPriority(): PASSED" << std::endl;

    // // test getPriority()
    // std::cout << ptr_post0->getPriority() << " Priority" << std::endl;
    // std::cout << "test getPriority(): PASSED" << std::endl;

    // std::cout << "\nTASK 1: PASSED\n\n";

    // TASK 2 TESTS
    Network<Account> net1;
    Account *ptr_user1 = new Account("user1", "pass1");
    net1.addAccount(ptr_user1);

    // Posts created oldest to newest
    Post *ptr_post1 = new General("title of general post 1", "this post was added first, has 3 likes", "user1");
    ptr_post1->like();
    ptr_post1->like();
    ptr_post1->like();
    ptr_post1->setPriority(ptr_post1->HIGH);

    Post *ptr_post2 = new General("title of general post 2", "this post was added second, has 2 likes", "user1");
    ptr_post2->like();
    ptr_post2->like();
    ptr_post2->setPriority(ptr_post2->LOW);

    Post *ptr_post3 = new General("title of general post 3", "this post was added third, has 4 likes", "user1");
    ptr_post3->like();
    ptr_post3->like();
    ptr_post3->like();
    ptr_post3->like();
    ptr_post3->setPriority(ptr_post3->HIGH);

    Post *ptr_post4 = new General("title of general post 4", "this post was added fourth, has 5 likes", "user1");
    ptr_post4->like();
    ptr_post4->like();
    ptr_post4->like();
    ptr_post4->like();
    ptr_post4->like();

    Post *ptr_post5 = new General("title of general post 5", "this post was added fifth, has 2 likes", "user1");
    ptr_post5->like();
    ptr_post5->like();
    ptr_post5->setPriority(ptr_post5->HIGH);

    Post *ptr_post6 = new General("title of general post 6", "this post was added sixth, has 5 likes", "user1");
    ptr_post6->like();
    ptr_post6->like();
    ptr_post6->like();
    ptr_post6->like();
    ptr_post6->like();

    // add posts to account
    ptr_user1->addPost(ptr_post1);
    ptr_user1->addPost(ptr_post2);
    ptr_user1->addPost(ptr_post3);
    ptr_user1->addPost(ptr_post4);
    ptr_user1->addPost(ptr_post5);
    ptr_user1->addPost(ptr_post6);

    // // TASK 2 TEST
    // std::cout << "TASK 2 TESTS:\n\n";

    // test getMinLikes()
    // ptr_user1->getMinLikes()->displayPost();
    // std::cout << "test getMinLikes(): PASSED" << std::endl;

    // std::cout << "MARKER" << std::endl;

    // // // test getMaxLikes()
    // ptr_user1->getMaxLikes()->displayPost();
    // std::cout << "test getMaxLikes(): PASSED" << std::endl;
    // std::cout << "MARKER" << std::endl;

    // test increasingPriorityOldestToNewest()
    std::cout << "\ntest increasingPriorityOldestToNewest()" << std::endl;
    std::vector<Post *> temp1 = ptr_user1->increasingPriorityOldestToNewest();
    for (int i = 0; i < temp1.size(); i++)
    {
        std::cout << temp1[i]->getPriority() << std::endl;
        temp1[i]->getTimeStamp();
        std::cout << std::endl;
    }
    std::cout << "test increasingPriorityOldestToNewest(): PASSED" << std::endl;

    // // test increasingPriorityNewestToOldest()
    // std::vector<Post *> temp2 = ptr_user1->increasingPriorityNewestToOldest();
    // std::cout << "\ntest increasingPriorityNewestToOldest()" << std::endl;
    // for (int j = 0; j < temp2.size(); j++)
    // {
    //     std::cout << temp2[j]->getPriority() << std::endl;
    //     temp2[j]->getTimeStamp();
    //     std::cout << std::endl;
    // }
    // std::cout << "test increasingPriorityNewestToOldest(): PASSED" << std::endl;

    // // test decreasingPriorityOldestToNewest()
    // std::vector<Post *> temp3 = ptr_user1->decreasingPriorityOldestToNewest();
    // std::cout << "\ntest decreasingPriorityOldestToNewest()" << std::endl;
    // for (int k = 0; k < temp3.size(); k++)
    // {
    //     std::cout << temp3[k]->getPriority() << std::endl;
    //     temp3[k]->getTimeStamp();
    //     std::cout << std::endl;
    // }
    // std::cout << "test decreasingPriorityOldestToNewest(): PASSED" << std::endl;

    // // test decreasingPriorityNewestToOldest()
    // std::vector<Post *> temp4 = ptr_user1->decreasingPriorityNewestToOldest();
    // std::cout << "\ntest decreasingPriorityNewestToOldest()" << std::endl;
    // for (int l = 0; l < temp4.size(); l++)
    // {
    //     std::cout << temp4[l]->getPriority() << std::endl;
    //     temp4[l]->getTimeStamp();
    //     std::cout << std::endl;
    // }
    // std::cout << "test decreasingPriorityNewestToOldest(): PASSED" << std::endl;

    // std::cout << ptr_post1->getTimeT() << " " << ptr_post6->getTimeT() << std::endl;

    // std::cout << "MARKER" << std::endl;

    // std::cout << "\nTASK 2: PASSED\n\n";

    // TASK 3 TEST
    // std::cout << "\nTASK 3 TESTS:\n";

    // // test updatePost()
    // // ptr_post4->like();
    // ptr_user1->updatePost(ptr_post4, "updated title for general post 4", "updated body for general post 4");
    // ptr_user1->getMaxLikes()->displayPost();
    // std::cout << "test updatePost(): PASSED" << std::endl;

    // std::cout << "MARKER" << std::endl;
    return 0;
}