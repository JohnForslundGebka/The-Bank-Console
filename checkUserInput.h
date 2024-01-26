#include <iostream>

int checkUserInput(int max, std::string message) 
{
    int number;
    while (true) 
    {
        std::cin >> number;

        if (std::cin.fail() || number < 1 || number > max) 
        {
            std::cout << "\tError: Invalid input. " << message;

            // Clear error flag
            std::cin.clear();

            // Ignore remaining input until the next newline
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else 
        {
            return number;
        }
    }
}

std::string checkCurrencyInput()
{
    bool validCurrency = false;
    std::string currencyInput;
    std::string acceptedCurrencies[6] = {"SEK", "USD", "DKK", "EUR", "NOK", "RSD"};

    std::cout << "\n\tWhich currency do you want to exchange to? ";
    
    do
    {
        std::cin >> currencyInput;

        //convert to input string to all caps
            for (char &c: currencyInput)
                c = std::toupper(c);

        for (std::string &temp : acceptedCurrencies)
        {
            if (temp == currencyInput)
            {
                validCurrency = true;
                return currencyInput;
            }
        }
        std::cout << "\n\tInvalid input! Please enter a valid currency: ";
    
    } while (!validCurrency);





}

