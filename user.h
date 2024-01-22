#include <iostream>
#include <vector>
#include <cctype>


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
    

    void createNewAccount()
    {
        std::string accountName;
        std::string currency;
        double amountOnAccount;

        std::cout << "\nMata in namn på ditt nya konto: ";
        std::cin >> accountName;
        std::cout << "\nVad är beloppet på ditt nya konto: ";
        std::cin >> amountOnAccount;
        std::cout << "\nVilken valuta skall ditt nya konto ha? (exempel KR eller USD)";
        std::cin >> currency;

        userAccounts.push_back(Account(accountName, amountOnAccount, currency));
    }


    const std::string & getUserName() {return userName;};

    int getPinCode() {return pinCode;};

   //print out all users accounts
    void printAllAccounts()
    {
        for (int i = 0; i < userAccounts.size(); i++)
        {
            std::cout << "\n";
            std::cout << i + 1;
            userAccounts[i].printAccount();

        }

        std::cout << "\n\t:";
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
            std::cout << "\nOmöjlig transaktion!";
        } else {
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
        int chosenAccount;
        char yesOrNo;
        double amountToExchange;
        double newAmount;
        std::string userInputString;
        bool foundCurrency = false;

        std::map<std::pair<std::string, std::string>, double> currencyConverter;
        currencyConverter[{"SEK", "DKK"}] = 0.65;
        currencyConverter[{"SEK", "EUR"}] = 0.088;
        currencyConverter[{"DKK", "SEK"}] = 1.53;
        currencyConverter[{"DKK", "EUR"}] = 0.13;
        currencyConverter[{"EUR", "SEK"}] = 11.41;
        currencyConverter[{"EUR", "DKK"}] = 7.46;

        std::cout << "\n\tChoose which account you want to exchange money from\n";
        printAllAccounts();
        std::cin >> chosenAccount;
        chosenAccount--;

        std::cout << "\n\tHow much money do you wish to exchange?\t:";
        std::cin >> amountToExchange;

        std::cout << "\n\tWhich currency do you whish to exchange to?\n\t"
                  <<  "Write your answer and press enter\n\t"
                  <<  "SEK\tUSD\tDKK\t:";
        std::cin >> userInputString;

        //convert to input string to all caps
        for (char &c: userInputString)
            c = std::toupper(c);

        //calculaate the new amount
        newAmount = amountToExchange * (currencyConverter[{userAccounts[chosenAccount].getCurrency(), userInputString}]);

        //checks if the user accepts the exchange
        std::cout << "\n\tFor your " << amountToExchange << userAccounts[chosenAccount].getCurrency() << " you will get "
                  << newAmount << " " << userInputString << ". Do you accept this exchange? y/n \t:";
        std::cin >> yesOrNo;

        //continues if user chooses yes
        if (yesOrNo=='y' || yesOrNo=='Y') {
            int whichAcountHasCurrency;

            //loops through all the account to see if the currency exists on users account
            for (int i = 0; i < userAccounts.size(); i++)
                if (userAccounts[i].getCurrency() == userInputString) {
                    foundCurrency = true;
                    whichAcountHasCurrency = i;
                    break;
                }

            if (foundCurrency) {
                userAccounts[chosenAccount].setAccountBalance(
                        userAccounts[chosenAccount].getAccountBalance() - amountToExchange);
                userAccounts[whichAcountHasCurrency].setAccountBalance(
                        userAccounts[whichAcountHasCurrency].getAccountBalance() + newAmount);
            } else {
                std::cout << "\n\tYou have no account with " << userInputString << "\n\tCreating new account";
                userAccounts.push_back(Account((userInputString + " Konto"), newAmount, userInputString));

            }
            return;
        }

    }


};





