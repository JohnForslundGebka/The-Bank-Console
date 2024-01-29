#ifndef THE_BANK_CONSOLE_LOGIN_H
#define THE_BANK_CONSOLE_LOGIN_H

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

#endif //THE_BANK_CONSOLE_LOGIN_H
