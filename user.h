#include <iostream>
#include <vector>



//class for user
class User
{

private:

    std::string userName;
    int pinCode;
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

    unsigned int getPinCode() {return pinCode;};

   //print out all users accounts
    void printAllAccounts()
    {
        for (int i = 0; i < userAccounts.size(); i++)
        {
            std::cout << i + 1;
            userAccounts[i].printAccount();
            std::cout << "\n";
        }
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
};



