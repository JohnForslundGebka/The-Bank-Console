#include <iostream>
#include "account.h"
#include "user.h"

//function that handles the login and pin validation
User & logIn(User users[])
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
           //check the pincode of the user
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
int main() {

    User users[5] =
            {
            {"Stefan", 1234},
            { "John", 5678 },
            {"Melker", 2345},
            {"Sebastian", 3456},
            {"Anas", 7890},
             };

    //main loop that runs the program
    while (true)
    {
        //create an object that points to the logged in user
        User activeUser = logIn(users);
        std::cout << "\n\tHello again " << activeUser.getUserName();
        break;
    }
}
