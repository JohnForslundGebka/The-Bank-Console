#include <iostream>
#include <vector>

//class for user
class User
{

private:
    std::string userName;
    int pinCode;
    std::vector<Account> userAccounts;//vector that contains the users accounts
    int userId;

public:
    User () : userName(""), pinCode(0) {};      //Default constructor

    //Constructor for initializing object with username and pin code.
    User (std::string _username, int _pinCode, int _userId) :  userName(std::move(_username)), pinCode(_pinCode), userId(_userId) {}
    

    //get methods
    const std::string & getUserName() {return userName;}
    int getPinCode() {return pinCode;}
    int getUserId() {return userId;}
    //set methods
    void setUsername(std::string _username) {userName=_username;}
    void setPincode(int _pinCode) {pinCode =_pinCode;}
    void setUserId(int _userId) {userId = _userId;}


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

    // Promts the user for a transfer of money from one account to another.
    void transfer() 
    {
        int from;
        int to;
        std::string tocurr;
        std::string fromcurr;
        double amount;
        printAllAccounts();

        std::cout << "\n\tSelect from which account you want to make transfer:\t ";
        from = checkUserInput(userAccounts.size(), "Please enter a valid digit from the list of accounts:");

        std::cout << "\n\tSelect to which account you want to make transfer:\t ";
        to = checkUserInput(userAccounts.size(), "Please enter a valid digit from the list of accounts:");
        
        while (true)
        {
            std::cout << "\n\tHow much:\t ";
            amount = checkUserInput(99999, "Please enter a valid amount: ");
            //adjust for index
            from -= 1;
            to -= 1;
            tocurr = userAccounts[to].getCurrency();
            fromcurr = userAccounts[from].getCurrency();
            //calculate the new amount, if the currencies are not the same, do a conversion
            double fixamount = getConversionRate(fromcurr, tocurr) * amount;
            //checks if the user has enough funds to complete the transfer
            if (userAccounts[from].getAccountBalance() < amount)
            {
                std::cout << "\n\tInsufficient funds  ---- Try a different amount!";
                continue;

            }
            //set new amounts to the accounts
            userAccounts[from].setAccountBalance(userAccounts[from].getAccountBalance() - amount);
            userAccounts[to].setAccountBalance(userAccounts[to].getAccountBalance() + fixamount);
            std::cout << "\tTransaction completed! Automatically converted currency.\n";
            return;
        }
    }

    //create a new account
    void fillAccountData(std::string name, double balance, std::string currency)
    {
        userAccounts.push_back(Account(name, balance, currency));
    }

    //convert to a different currency
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

        // Makes sure user input choice is valid
        chosenAccount = checkUserInput(userAccounts.size(), "Please enter a valid account from the list of accounts: ");
        chosenAccount--;

        do
        {
            std::cout << "\n\tWhich currency do you whish to exchange to?\n\t"
                    <<  "Write your answer and press enter\n\t"
                    <<  "SEK\tUSD\tDKK\tEUR\tNOK\tRSD\t:";
            userInputString = checkCurrencyInput();  //checks that the user has input a supported currency
            
            std::cout << "\n\tHow much money do you wish to exchange?\t:";
            amountToExchange = checkUserInput(999999, "Please enter a valid amount: ");  //Making sure input is correct

            //calculate the new amount
            newAmount = amountToExchange * (getConversionRate(userAccounts[chosenAccount].getCurrency(), userInputString));

            if(amountToExchange > userAccounts[chosenAccount].getAccountBalance())
            {
                std::cout << "\n\tInsufficient funds  ---- Try a different amount!\n";
                continue;
            }
        } while (newAmount == 0);


        while (true) {
            //checks if the user accepts the exchange
            std::cout << "\n\tFor your " << amountToExchange << userAccounts[chosenAccount].getCurrency()
                      << " you will get "
                      << newAmount << " " << userInputString << ". Do you accept this exchange? y/n \t:";
            std::cin >> yesOrNo;

            //continues if user chooses yes
            if (yesOrNo == 'y' || yesOrNo == 'Y') {
                int whichAcountHasCurrency;

                //loops through all the account to see if the currency exists on users account
                for (int i = 0; i < userAccounts.size(); i++)
                    if (userAccounts[i].getCurrency() == userInputString) {
                        foundCurrency = true;
                        whichAcountHasCurrency = i;
                        break;
                    }
                //if user has a account with the right currency, do the transfer
                if (foundCurrency)
                {
                    userAccounts[chosenAccount].setAccountBalance(
                            userAccounts[chosenAccount].getAccountBalance() - amountToExchange);

                    userAccounts[whichAcountHasCurrency].setAccountBalance(
                            userAccounts[whichAcountHasCurrency].getAccountBalance() + newAmount);
                } else
                {
                    std::cout << "\n\tYou have no account with " << userInputString << "\n\tCreating new account..."
                              << "\n\tAccount created! Money transfered!\n";
                    userAccounts.push_back(Account((userInputString + " Account"), newAmount, userInputString));
                    userAccounts[chosenAccount].setAccountBalance(
                            userAccounts[chosenAccount].getAccountBalance() - amountToExchange);
                }
                return;
            } else if (yesOrNo == 'n' || yesOrNo == 'N')
            {
                std::cout << "\n\tTransaction canceled";
                return;
            } else
            {
                std::cout << "\n\tWrong input. Please enter y or n\n";
            }
        }
    }
};