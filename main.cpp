#include <iostream>
#include "checkUserInput.h"
#include "account.h"
#include "user.h"
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>


void clearScreen() 
{
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
               std::cout << "\n\tHello " << users[i].getUserName() << " please enter your pincode\n\tYou have"
                         << " 3 attempts:\t";
               for (int j = 0; j < 3; j++)     //for loop that checks the pincode
               {
                   
                   userInputPinCode = checkUserInput(9999, "Please enter a valid pincode: ");          //Making sure the input for pincode is valid.
                   if (userInputPinCode == users[i].getPinCode())    //if the pincode matches, return the active user
                       return users[i];

                   //end the program if user tries to enter pincode three times
                   if (j==2)
                   {
                       std::cout << "\n\tYou have entered the wrong pincode to many times. \nProgram closing...\n";
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


    SQLite::Database db("bankDatabase.db");

    for (int i = 0; i < 5; i++)
    {
       SQLite::Statement query(db, "SELECT account_name, balance, currency FROM accounts WHERE user_id = "+std::to_string(_users[i].getUserId()));
        try
        {
              while (query.executeStep())
              {
                   _users[i].fillAccountData(query.getColumn(0),query.getColumn(1),query.getColumn(2));
              }
        }
        catch (std::exception& e)
            {
                std::cout << "exception: " << e.what() << std::endl;
           }
    }
}



void menu(User &activeUser)
{
    int menuChoice;

    clearScreen(); 
    std::string input;
    std::cout << "\n\t" << activeUser.getUserName() << "s main menu " << std::endl;
    std::cout << "\t1.   See your accounts and balance\n"
              << "\t2.   Transfer money\n"
              << "\t3.   Exchange money\n"
              << "\t4.   Log out\n"
              << "\tChoice: ";
    
    // Calls the input function making sure the user inputs a valid menu choice.
    menuChoice = checkUserInput(4, "Please enter a valid choice from the menu: ");

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
            std::cout << "\n\tERROR! Wrong input";
            break;
    }
}

int main() 
{

    // Open a database file
    SQLite::Database db("bankDatabase.db");
    //create a query for all the users
    SQLite::Statement query(db, "SELECT * FROM users");

    //create five users
    User users[5] = {};

    //fill the five users with data from the database
     try
        {
           int userCounter = 0;

           while (query.executeStep())
           {
                users[userCounter].setUsername(query.getColumn(0));
                users[userCounter].setPincode(query.getColumn(1));
                users[userCounter].setUserId(query.getColumn(2));
                userCounter++;
           }
        }
     catch (std::exception& e)
         {
             std::cout << "exception: " << e.what() << std::endl;
        }


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