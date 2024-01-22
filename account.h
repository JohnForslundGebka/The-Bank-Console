#ifndef THE_BANK_CONSOLE_ACCOUNT_H
#define THE_BANK_CONSOLE_ACCOUNT_H
#include <iostream>
#include <utility>
#include <map>


//Class that hold the information about a account
class Account
{

private:
    std::string accountName;
    double accountBalance;
    std::string currency;


public:
    Account(std::string name, double balance, std::string curr)
    {
        accountName = name;
        currency = curr;
        accountBalance = balance;

    }

    void printAccount()
    {
        std::cout << ".\tAccount name: " <<  accountName << "\tBalance: " << accountBalance << " " << currency << "\n";
    }

    double getAccountBalance() {return accountBalance;}
    void setAccountBalance(double _newBalance) {accountBalance = _newBalance;}

    std::string getCurrency() {return currency;}
    


};





#endif //THE_BANK_CONSOLE_ACCOUNT_H
