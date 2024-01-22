#include <iostream>
#include "account.h"
#include "user.h"

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

// This function is called once in the beginning of the program to create and fill all users acounts. 
void fillAccounts(User _users[])
{
// User 0
    _users[0].fillAccountData("Resekonto", 5000, "SEK");
    _users[0].fillAccountData("Investeringssparkonto", 500, "EUR");
    _users[0].fillAccountData("Fritidskonto", 6000, "DKK");

// User 1
    _users[1].fillAccountData("Barnspar", 3000, "DKK");
    _users[1].fillAccountData("Nödkonto", 700, "EUR");

// User 2
    _users[2].fillAccountData("Huslån", 100000, "SEK");
    _users[2].fillAccountData("Bilsparkonto", 15000, "DKK");
    _users[2].fillAccountData("Julsparkonto", 1000, "EUR");
    _users[2].fillAccountData("Presentkonto", 4500, "SEK");
    _users[2].fillAccountData("Teknikspar", 20000, "DKK");

// User 3
    _users[3].fillAccountData("Matkonto", 8000, "DKK");
    _users[3].fillAccountData("Renoveringsfond", 1000, "EUR");

// User 4
    _users[4].fillAccountData("Pensionspar", 40000, "EUR");
    _users[4].fillAccountData("Drömprojekt", 25000, "SEK");
    _users[4].fillAccountData("Utbildningsfond", 15000, "DKK");
    _users[4].fillAccountData("Hobbykonto", 7000, "EUR");
    _users[4].fillAccountData("Klädkonto", 5000, "SEK");
    _users[4].fillAccountData("Samlarkonto", 3000, "DKK");

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
        std::cout << "\n\tHello again " << activeUser.getUserName() << std::endl;

        activeUser.converter();

        activeUser.printAllAccounts();

        break;
    }   
}
