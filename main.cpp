#include <iostream>
#include "account.h"
#include "user.h"

//function that handles the login and pin validation
User & logIn(User users[])
{
   std::string userInputName;
   int userInputPinCode;

   while(true)
   {
       std::cin >> userInputName;

       for (int i = 0; i<5;i++)
       {
           if (userInputName==users[i].)

       }



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

        std::cout << "\n\t\tWelcome to the bank of Chas"
                  << "\n\t===================================\n"
                  << "\n\tPlease enter your username and press enter:\t";
        break;

    }


}
