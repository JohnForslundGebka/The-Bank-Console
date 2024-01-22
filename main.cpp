#include <iostream>
#include "account.h"
#include "user.h"

void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("cls");
#else
    std::system("clear");
#endif
}

//function that handles the login and pin validation
User &logIn(User users[])
{
   std::string userInputName;
   int userInputPinCode;
   std::cout << "\n\t\tWelcome to the bank of Chas"
           << "\n\t===================================\n"
           << "\n\tPlease enter your username and press enter:\t";
   //Loop that runs while checking the users name
   while(true)
   {
       std::cin >> userInputName;

       //Loop that runs and checks if the username input matches an existing username
       for (int i = 0; i<5;i++)
       {

           if (userInputName==users[i].getUserName())
           {
               std::cout << "\n\tHello " << users[i].getUserName() << " please enter your pincode\n\tyou have"
                         << " three attempts:\t";
               for (int j = 0; j < 3; j++)     //for loop that checks the pincode
               {
                   std::cin >> userInputPinCode;
                   if (userInputPinCode == users[i].getPinCode())    //if the pincode matches, return the active user
                       return users[i];

                   //end the program if user tries to enter pincode three times
                   if (j==2)
                   {
                       std::cout << "\n\tYou have entered the wrong pincode to many times\n";
                       exit(EXIT_FAILURE);
                   } else
                   std::cout << "\n\tERROR! Wrong pincode, please try again:\t";
               }
           }
       }
       std::cout << "\n\tUser not found. Please try again:\t";
   }
}

//enum for menu choice
enum menuSelection
{
    SEE_ACOUNTS = 1,
    TRANSFER = 2,
    EXCHANGE = 3,
    LOG_OUT = 4,
};


// This function is called once in the beginning of the program to create and fill all users acounts. 
void fillAccounts(User _users[])
{
// User 0
    _users[0].fillAccountData("Travel", 5000, "SEK");
    _users[0].fillAccountData("Investment", 500, "EUR");
    _users[0].fillAccountData("Free time", 6000, "DKK");

// User 1
    _users[1].fillAccountData("Children", 3000, "DKK");
    _users[1].fillAccountData("Emergency", 700, "EUR");

// User 2
    _users[2].fillAccountData("House", 100000, "SEK");
    _users[2].fillAccountData("Car saving", 15000, "DKK");
    _users[2].fillAccountData("Christmas", 1000, "EUR");
    _users[2].fillAccountData("Presents", 4500, "SEK");
    _users[2].fillAccountData("Tech", 20000, "DKK");

// User 3
    _users[3].fillAccountData("Food", 8000, "DKK");
    _users[3].fillAccountData("Renovering", 1000, "EUR");

// User 4
    _users[4].fillAccountData("Pension", 40000, "EUR");
    _users[4].fillAccountData("Dream project", 25000, "SEK");
    _users[4].fillAccountData("Study fond", 15000, "DKK");
    _users[4].fillAccountData("Hobby", 7000, "EUR");
    _users[4].fillAccountData("Clothes", 5000, "SEK");
    _users[4].fillAccountData("Collection", 3000, "DKK");

}


void menu(User &activeUser)
{
    int menuChoice;
    std::string input;
    std::cout << "\n\t" << activeUser.getUserName() << "s main menu " << std::endl;
    std::cout << "\t1.   See your accounts and balance\n"
              << "\t2.   Transfer money\n"
              << "\t3.   Exchange money\n"
              << "\t4.   Log out\n"
              << "\t:";
    std::cin >> menuChoice;

    switch (menuChoice)
    {
        case SEE_ACOUNTS :
            clearScreen();
            activeUser.printAllAccounts();
            std::cout << "\n\tPress enter to exit to main menu";
            std::getline(std::cin, input);
            if (std::cin.ignore(256,'\n'))
            {
                clearScreen();
                menu(activeUser);
            }
            break;


        case TRANSFER :
            activeUser.transfer();
            std::cout << "\n\tPress enter to exit to main menu";
            std::getline(std::cin, input);
            if (std::cin.ignore(256,'\n'))
            {
                clearScreen();
                menu(activeUser);
            }
            break;


        case EXCHANGE :
            activeUser.converter();
            std::cout << "\n\tPress enter to exit to main menu";
            std::getline(std::cin, input);
            if (std::cin.ignore(256,'\n'))
            {
                clearScreen();
                menu(activeUser);
            }
            break;

        case LOG_OUT :
            clearScreen();
            return;

        default:
            std::cout << "\n\tERROR wrong input";
            break;

    }
}

int main() {

    User users[5] =
    {
        {"Stefan", 1234},
        {"John", 5678 },
        {"Melker", 2345},
        {"Sebastian", 3456},
        {"Anas", 7890},
    };
    //This functions fills all of the users acounts with data
    fillAccounts(users);

    //main loop that runs the program
    while (true)
    {
        //create an object that points to the logged in user
        User activeUser = logIn(users);
        menu(activeUser);

    }   
}
