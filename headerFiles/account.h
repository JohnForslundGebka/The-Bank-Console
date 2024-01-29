#ifndef THE_BANK_CONSOLE_ACCOUNT_H
#define THE_BANK_CONSOLE_ACCOUNT_H
#include <iostream>
#include <utility>
#include <iomanip>

//Class that hold the information about a account
class Account
{
private:
    std::string accountName;
    double accountBalance;
    std::string currency;

public:
    Account(std::string name, double balance, std::string curr) : accountName(std::move(name)), accountBalance(balance), currency(std::move(curr)) {}

    void printAccount()
    {
        const int nameWidth = 20;
        std::cout << "." << std::left << std::setw(nameWidth) << accountName
                  << "Balance: " << accountBalance << " " << currency;
    }

    //get methods
    double getAccountBalance() {return accountBalance;}
    std::string getCurrency() {return currency;}
    //set method
    void setAccountBalance(double _newBalance) {accountBalance = _newBalance;}

};

#endif //THE_BANK_CONSOLE_ACCOUNT_H