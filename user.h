#include <iostream>
#include <vector>
#include <cctype>

double getConversionRate(const std::string& fromCurrency, const std::string& toCurrency)
{
    std::map<std::pair<std::string, std::string>, double> currencyConverter;

    // Fill the map with currency conversion rates
    currencyConverter[{"SEK", "NOK"}] = 1.0;
    currencyConverter[{"SEK", "DKK"}] = 0.65;
    currencyConverter[{"SEK", "EUR"}] = 0.088;
    currencyConverter[{"SEK", "USD"}] = 0.096;
    currencyConverter[{"SEK", "RSD"}] = 10.26;
    currencyConverter[{"DKK", "NOK"}] = 1.53;
    currencyConverter[{"DKK", "SEK"}] = 1.53;
    currencyConverter[{"DKK", "EUR"}] = 0.13;
    currencyConverter[{"DKK", "USD"}] = 0.15;
    currencyConverter[{"DKK", "RSD"}] = 15.69;
    currencyConverter[{"EUR", "NOK"}] = 11.43;
    currencyConverter[{"EUR", "SEK"}] = 11.4;
    currencyConverter[{"EUR", "DKK"}] = 7.46;
    currencyConverter[{"EUR", "USD"}] = 1.09;
    currencyConverter[{"EUR", "RSD"}] = 117.21;
    currencyConverter[{"USD", "NOK"}] = 10.46;
    currencyConverter[{"USD", "SEK"}] = 10.46;
    currencyConverter[{"USD", "DKK"}] = 6.84;
    currencyConverter[{"USD", "EUR"}] = 0.92;
    currencyConverter[{"USD", "RSD"}] = 107.38;
    currencyConverter[{"RSD", "NOK"}] = 0.097;
    currencyConverter[{"RSD", "SEK"}] = 0.097;
    currencyConverter[{"RSD", "DKK"}] = 0.064;
    currencyConverter[{"RSD", "EUR"}] = 0.0085;
    currencyConverter[{"RSD", "USD"}] = 0.0093;
    currencyConverter[{"NOK", "SEK"}] = 0.99;
    currencyConverter[{"NOK", "DKK"}] = 0.65;
    currencyConverter[{"NOK", "EUR"}] = 0.087;
    currencyConverter[{"NOK", "USD"}] = 0.095;

    return currencyConverter[{fromCurrency, toCurrency}];
}

//class for user
class User
{

private:

    std::string userName;
    const int pinCode;
    std::vector<Account> userAccounts;//vector that contains the users accounts
public:
    User () : userName(""), pinCode(0) {};//Default constructor

    //Constructor for initializing object with username and pin code.
    User (std::string _username, int _pinCode) :  userName(std::move(_username)), pinCode(_pinCode) {}
    

    const std::string & getUserName() {return userName;};

    int getPinCode() {return pinCode;};


   //print out all users accounts
   void printAllAccounts()
   {
       std::cout << "\n\t=========ACCOUNT STATUS=========:\n";
       for (int i = 0; i < userAccounts.size(); i++)
       {
           std::cout << "\n\t" << i + 1;
           userAccounts[i].printAccount();
       }
       std::cout << std::endl;
   }

    // Promts the user for a transfer of money from one acount to another.
    void transfer()
    {
        int from;
        int to;
        double amount;
        
        printAllAccounts();

        std::cout << "\n\tMata in vilket konto du vill föra över från:\t ";
        std::cin >> from;
        std::cout << "\n\tMata in vilket konto du vill föra över till:\t ";
        std::cin >> to;
        std::cout << "\n\tHur mycket:\t ";
        std::cin >> amount;

        from -= 1; 
        to -= 1; 

        if (userAccounts[from].getAccountBalance() < amount)
        {
            std::cout << "\nERROR! Unpossible transaction!";
        } else 
        {
            userAccounts[from].setAccountBalance(userAccounts[from].getAccountBalance() - amount);
            userAccounts[to].setAccountBalance(userAccounts[to].getAccountBalance() + amount);
        }  
    }

    // This function is used for accessing the private member vector "userAccounts" and initialize
    // the users acounts. 
    void fillAccountData(std::string name, double balance, std::string currency)
    {
        userAccounts.push_back(Account(name, balance, currency));
    }

    void converter()
    {
        //create variables that will be used
        int chosenAccount;
        char yesOrNo;
        double amountToExchange;
        double newAmount;
        std::string userInputString;
        bool foundCurrency = false;

        printAllAccounts();
        std::cout << "\n\tChoose which account you want to exchange money from\t:";

        std::cin >> chosenAccount;
        chosenAccount--;

        std::cout << "\n\tHow much money do you wish to exchange?\t:";
        std::cin >> amountToExchange;

        std::cout << "\n\tWhich currency do you whish to exchange to?\n\t"
                  <<  "Write your answer and press enter\n\t"
                  <<  "SEK\tUSD\tDKK\tEUR\tNOK\tRSD\t:";
        std::cin >> userInputString;

        //convert to input string to all caps
        for (char &c: userInputString)
            c = std::toupper(c);

        //calculate the new amount
        newAmount = amountToExchange * (getConversionRate(userAccounts[chosenAccount].getCurrency(), userInputString));

        //checks if the user accepts the exchange
        std::cout << "\n\tFor your " << amountToExchange << userAccounts[chosenAccount].getCurrency() << " you will get "
                  << newAmount << " " << userInputString << ". Do you accept this exchange? y/n \t:";
        std::cin >> yesOrNo;

        //continues if user chooses yes
        if (yesOrNo=='y' || yesOrNo=='Y')
        {
            int whichAcountHasCurrency;

            //loops through all the account to see if the currency exists on users account
            for (int i = 0; i < userAccounts.size(); i++)
                if (userAccounts[i].getCurrency() == userInputString)
                {
                    foundCurrency = true;
                    whichAcountHasCurrency = i;
                    break;
                }
            //if user has a account with the right currency, do the transfer
            if (foundCurrency)
            {
                userAccounts[chosenAccount].setAccountBalance(userAccounts[chosenAccount].getAccountBalance() - amountToExchange);

                userAccounts[whichAcountHasCurrency].setAccountBalance(userAccounts[whichAcountHasCurrency].getAccountBalance() + newAmount);
            } else
            {
                std::cout << "\n\tYou have no account with " << userInputString << "\n\tCreating new account";
                userAccounts.push_back(Account((userInputString + " Konto"), newAmount, userInputString));
                userAccounts[chosenAccount].setAccountBalance(
                        userAccounts[chosenAccount].getAccountBalance() - amountToExchange);
            }
            return;
        }
    }
};