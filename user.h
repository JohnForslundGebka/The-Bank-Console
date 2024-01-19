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
        std::cout << "\nVilken valuta skall ditt nya konto ha?";
        std::cin >> currency;
        std::cout << "\nVad är beloppet på ditt nya konto: ";
        std::cin >> amountOnAccount;

        userAccounts.push_back(Account(accountName, currency, amountOnAccount));
    }


    const std::string & getUserName() {return userName;};

    unsigned int getPinCode() {return pinCode;};


    void printAllAccounts()
    {
        for (int i = 0; i < userAccounts.size(); i++)
        {
            std::cout << i + 1;
            userAccounts[i].printAccount();
            std::cout << "\n";
        }
    }

    void transfer()
    {
        int from;
        int to;
        double amount;
        
        printAllAccounts();

        std::cout << "\nMata in vilket konto du vill föra över från: ";
        std::cin >> from;
        std::cout << "\nMata in vilket konto du vill föra över till: ";
        std::cin >> to;
        std::cout << "\nHur mycket ";
        std::cin >> amount;

        from -= 1; 
        to -= 1; 

        if (userAccounts[from].getAccountBalance() < amount){
            std::cout << "\nOmöjlig transaktion!";
        } else {
            userAccounts[from].setAccountBalance(userAccounts[from].getAccountBalance() - amount);
            userAccounts[to].setAccountBalance(userAccounts[to].getAccountBalance() + amount);
        }






       
    }
};



