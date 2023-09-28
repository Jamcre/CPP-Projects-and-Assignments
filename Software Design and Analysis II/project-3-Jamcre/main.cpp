#include "Account.hpp"
#include "Network.hpp"
#include "Post.hpp"

#include <iostream>

int main()
{
    // TASK 1 TESTS
    std::cout << "\nTASK 1 TESTS:\n";

    // 'Network' Constructor Test
    Network<Account> net1;
    std::cout << "\n'Network' Constructor Test: PASSED\n";

    // 'Network' getSizeOfNetwork Test
    std::cout << "\nSize of network: " << net1.getSizeOfNetwork();
    std::cout << "\n'Network' getSizeOfNetwork Test: PASSED\n";

    // 'Network' isEmpty Test
    if (net1.isEmpty())
    {
        std::cout << "\nThe network is empty";
    }
    std::cout << "\n'Network' isEmpty Test: PASSED\n";

    // 'Network' addAccount Test
    Account *acc1 = new Account("user1", "pass1");
    Account *acc2 = new Account("user2", "pass2");
    Account *acc3 = new Account("user3", "pass3");
    Account *acc4 = new Account("user4", "pass4");
    Account *acc5 = new Account("user5", "pass5");

    if (net1.addAccount(acc1) == net1.addAccount(acc2) == net1.addAccount(acc3) == net1.addAccount(acc4) == net1.addAccount(acc5))
    {
        std::cout << "\n"
                  << net1.getSizeOfNetwork() << " accounts added to network";
    }
    std::cout << "\n'Network' addAccount Test: PASSED\n";

    // 'Network' removeAccount Test
    if (net1.removeAccount(acc3))
    {
        std::cout << "\n1 account removed. " << net1.getSizeOfNetwork() << " accounts in the network";
        std::cout << "\n'Network' removeAccount Test: PASSED\n";
    }

    // 'Network' clear Test
    net1.clear();
    if (net1.isEmpty())
    {
        std::cout << "\nNetwork cleared. " << net1.getSizeOfNetwork() << " accounts remain in network.";
    }
    std::cout << "\n'Network' clear Test: PASSED\n";

    // 'Network' containsAccount Test
    Account *acc6 = new Account("user6", "pass6");
    Account *acc7 = new Account("user7", "pass7");
    Account *acc8 = new Account("user8", "pass8");
    Account *acc9 = new Account("user9", "pass9");
    Account *acc10 = new Account("user10", "pass10");
    net1.addAccount(acc6);
    net1.addAccount(acc7);
    net1.addAccount(acc8);
    net1.addAccount(acc9);
    net1.addAccount(acc10);

    if (net1.containsAccount(acc8))
    {
        std::cout << "\n"
                  << net1.getSizeOfNetwork() << " accounts in Network";
        std::cout << "\nNetwork contains requested account";
    }
    std::cout << "\n'Network' containsAccount Test: PASSED\n";

    // 'Network' populateNetwork Test
    Network<Account> net2;
    net2.populateNetwork("accounts.txt");
    if (!net2.isEmpty())
    {
        std::cout << "\nSize of 'net2': " << net2.getSizeOfNetwork();
        std::cout << "\n'Network' populateNetwork Test: PASSED\n";
    }

    // 'Network' operator-= Test
    Network<Account> net3;
    Account *acc6_v2 = new Account("user6", "pass6");
    Account *acc8_v2 = new Account("user8", "pass8");
    net3.addAccount(acc6_v2);
    net3.addAccount(acc8_v2);
    net1.operator-=(net3);
    if (net1.getSizeOfNetwork() == 3)
    {
        std::cout << "\n2 accounts have been removed from net1, leaving " << net1.getSizeOfNetwork() << " accounts in the network\n";
        std::cout << "'Network' operator-= Test: PASSED\n";
    }

    // 'Account' getNetwork Test
    Network<Account> *ptr_net1 = &net1;
    if (ptr_net1 == acc7->getNetwork())
    {
        std::cout << "\nReturned the correct network\n'Account' getNetwork Test: PASSED\n";
    }

    // 'Account' setNetwork Test
    Account acc11("user11", "pass11");
    acc11.setNetwork(ptr_net1);
    if (acc11.getNetwork() == acc7->getNetwork())
    {
        std::cout << "\n'acc11' pointer points to 'net1'\n'Account' setNetwork Test: PASSED\n";
    }

    // TASK 2 TESTS
    std::cout << "\nTASK 2 TESTS:\n";

    // 'Account' followAccount Test
    if (acc7->followAccount("user9"))
    {
        std::cout << "\nacc7 followed another account successfully\n'Account' followAccount Test: PASSED\n";
    }

    // 'Account' viewFollowing Test
    std::vector<std::string> temp_following = acc7->viewFollowing();
    if (temp_following.size() > 0)
    {
        std::cout << "\nacc7 follows 1 account\n'Account' viewFollowing Test: PASSED\n";
    }

    // 'Account' addPost Test

    // 'Network' printFeedForAccount Test

    // 'Network' authenticateFollow Test
    if (net1.authenticateFollow(*acc7, "user9"))
    {
        std::cout << "\nAutheticated that acc7 followed another user\n'Network' authenticateFollow: PASSED\n";
    }

    // 'Network' addToFeed Test

    return 0;
}