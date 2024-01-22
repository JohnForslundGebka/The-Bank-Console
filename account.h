#ifndef THE_BANK_CONSOLE_ACCOUNT_H
#define THE_BANK_CONSOLE_ACCOUNT_H
#include <iostream>
#include <utility>
#include <map>

void converter()
{
    std::map<std::pair<std::string, std::string>, double> currencyConverter;
    currencyConverter[{"SEK", "DKK"}] = 0.65;
    currencyConverter[{"SEK", "USD"}] = 0.096;
    currencyConverter[{"DKK", "SEK"}] = 1.53;
    currencyConverter[{"DKK", "USD"}] = 0.15;
    currencyConverter[{"USD", "SEK"}] = 10.46;
    currencyConverter[{"USD", "DKK"}] = 6.84;


}

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
    


};





#endif //THE_BANK_CONSOLE_ACCOUNT_H
