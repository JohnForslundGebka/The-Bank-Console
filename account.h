#ifndef THE_BANK_CONSOLE_ACCOUNT_H
#define THE_BANK_CONSOLE_ACCOUNT_H
#include <iostream>

//Class that hold the information about a account
class Account
{

private:
    std::string accountName;
    std::string currency;
    double accountBalance;


public:
    Account(std::string name, std::string curr, double balance)
    {
        accountName = name;
        currency = curr;
        accountBalance = balance;

    }



};





#endif //THE_BANK_CONSOLE_ACCOUNT_H
