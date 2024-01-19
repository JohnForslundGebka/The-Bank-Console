#ifndef THE_BANK_CONSOLE_ACCOUNT_H
#define THE_BANK_CONSOLE_ACCOUNT_H
#include <iostream>

//Class that hold the information about a account
class Account
{

private:
    std::string accountName;
    double accountBalance;
    std::string currency;


public:
    Account(std::string name, std::string curr, double balance)
    {
        accountName = name;
        currency = curr;
        accountBalance = balance;

    }

    void printAccount()
    {
        std::cout << "\tAccount name: " <<  accountName << "\tBalance: " << accountBalance << " " << currency << "\n"; 
    }

    double getAccountBalance() {return accountBalance;}

    void setAccountBalance(double _newBalance) {accountBalance = _newBalance;}
    


};





#endif //THE_BANK_CONSOLE_ACCOUNT_H
