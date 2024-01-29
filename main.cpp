#include <iostream>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>
#include "checkUserInput.h"
#include "conversionRate.h"
#include "account.h"
#include "user.h"
#include "login.h"
#include "fillData.h"

//Clears the console screen, different command if user has windows or mac
void clearScreen() 
{
    #if defined(_WIN32) || defined(_WIN64)
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

//enum for menu choice
enum menuSelection
{
    SEE_ACOUNTS = 1,
    TRANSFER = 2,
    EXCHANGE = 3,
    LOG_OUT = 4,
};

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
    //create five users
    User users[5] = {};

    //get all the data from the database and put it into the user classes
    fillData(users);

    //main loop that runs the program
    while (true)
    {
        //create an object that points to the logged in user
        User activeUser = logIn(users);
        menu(activeUser);
    }   
}