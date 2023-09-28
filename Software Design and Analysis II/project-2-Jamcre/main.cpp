#include <iostream>
#include "Post.hpp"
#include "General.hpp"
#include "Poll.hpp"
#include "Promotional.hpp"
#include <vector>

int main()
{

    /*
    // TASK 1 TESTS
    std::cout << std::endl
              << "TASK 1: TEST GENERAL CLASS" << std::endl;

    // TEST CONSTRUCTOR
    General gen1("Chicken came before the egg confirmed!",
                 "A new story just released where we finally get the answer of who came first.",
                 "jim111");

    // TEST 'reactToPost();'
    gen1.reactToPost(LIKE);
    gen1.reactToPost(LIKE);
    gen1.reactToPost(LIKE);
    gen1.reactToPost(LIKE);    // 4 'LIKE' REACTIONS
    gen1.reactToPost(DISLIKE); // 1 'DISLIKE' REACTION
    gen1.reactToPost(LAUGH);
    gen1.reactToPost(LAUGH);
    gen1.reactToPost(LAUGH); // 3 'LAUGH' REACTIONS
    gen1.reactToPost(WOW);
    gen1.reactToPost(WOW); // 2 'WOW' REACTIONS
    gen1.reactToPost(SAD);
    gen1.reactToPost(SAD);   // 2 'SAD' REACTIONS
    gen1.reactToPost(ANGRY); // 1 'ANGRY' REACTION

    // TEST 'getReactions();'
    std::cout << std::endl;
    gen1.getReactions();

    // TEST 'displayPost();'
    gen1.displayPost();
    */

    //
    // TASK 2 TESTS
    std::cout << std::endl
              << "TASK 2: TEST POLL CLASS" << std::endl;

    std::vector<std::string> v;
    v.push_back("Vanillas");
    v.push_back("Chocalate");
    v.push_back("Mint");

    // TEST CONSTRUCTOR
    Poll poll1("Title of 'Poll' post!", "Body of the 'Poll' Post, hopefully this will work but it probably wont't.", "AUGHH2", v);

    // TEST 'votePoll()'
    poll1.votePoll(0);
    poll1.votePoll(0);
    poll1.votePoll(0);
    poll1.votePoll(1);
    poll1.votePoll(1);

    // TEST 'changePollOptions()'
    poll1.changePollOption("Cookie", 7);

    // TEST 'getPollOptions()'
    poll1.getPollOptions();

    // TEST 'getPollVotes()'
    std::cout << "\n"
              << std::to_string(poll1.getPollVotes(1)) << " for index 2 of poll_options_" << std::endl;

    // TEST 'displayPost()'
    poll1.displayPost();
    //

    //
    // TASK 3 TESTS
    std::cout << std::endl
              << "TASK 3: TEST PROMOTIONAL CLASS" << std::endl;

    // TEST CONSTRUCTOR

    Promotional pro1("title for 'Promotional'!",
                     "This is the body for the 'Promotional' post I am writing. Hopefully this works first try but it probably won't.",
                     "BingBong12",
                     "https://something.com");

    // TEST 'displayPost()'
    pro1.displayPost();

    // TEST 'setLink()'
    pro1.setLink("AAAA");
    pro1.displayPost();

    pro1.setLink("https://helo&0.c");

    // TEST 'displayPost()'
    pro1.displayPost();

    //
}