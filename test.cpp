#include<iostream>
#include<vector>

class Account
{
   
    

public:
    std::string accountName;
    float amountOnAccount;
    Account() : accountName("konto"), amountOnAccount(0) {}
    Account(std::string name, float amount) : accountName(name), amountOnAccount(amount) {}
    
    void printAccount()
    {
        std::cout << "\n" << accountName << "\t" << amountOnAccount << "\n";
    }
};

class Customer
{  
private:
    std::string username;
    std::string password;
    

public:
    std::vector<Account>customerAccounts; 

    //Default konstruktor
    Customer () : username(""), password("") {};
    
    Customer (std::string user, std::string passw)
    {
        username = user;
        password = passw;
    }

    void setUserInfo (std::string user, std::string passw)
    {
        username = user;
        password = passw;
        std::string name;
        float amount{0}; 
        std::cout << "\nSkriv in namn följt av summa på ditt nya konto: ";
        std::cin >> name >> amount;
        customerAccounts.push_back(Account(name, amount));    
    }
    void printCustomerInfo()
    {
        std::cout << "Username: " << username 
        << "\nPassword: " << password;

        for (int i = 0; i < customerAccounts.size(); i++)
        {
           customerAccounts[i].printAccount();
        }
        std::cout << "\n";
    }

    void addAccount()
    {
        float amount = 0;
        std::string name;
        std::cout << "\nMata in namn på nytt konto följt av beloppet: ";
        std::cin >> name >> amount;

        customerAccounts.push_back(Account(name, amount));
    }

    void transaction()
    {
        float amount = 0;
        int a;
        int b;
        std::cout << "Mata först in kontot du vill föra över FRÅN följt av kontot pengarna skall till: ";
        std::cin >> a >> b;
        std::cout << "Mata in belopp som skall föras över: ";
        std::cin >> amount; 

        customerAccounts[a].amountOnAccount -= amount;
        customerAccounts[b].amountOnAccount += amount; 
    }

    bool InputValidPassword()
    {
        std::string passwordInput;
    
        for(int i = 0; i < 3; i++)
        {
            std::string passwordInput = " ";
            std::cout << "\nSkriv in lösenord för användare \"" << getUsername() << "\":";
            std::cin >> passwordInput;
            if (passwordInput == password)
                return true;
            else
            {
                std::cout << "\nFel lösenord, försök igen!";

                if(i == 1)
                    std::cout << "\nDu har bara ett försök kvar innan programmet avslutas.";
                if(i == 2)
                {
                    std::cout << "\nDu har matat in fel lösenord tre gånger och programmet avslutas.";
                    return false; 
                }
            }
        }
        
    }

    std::string getUsername()
    {
        return username;
    }

};

int inputUsername(Customer customer[])
{
    bool isValidUsername = false;
    std::string username;

    while (!isValidUsername)
    {
        std::cout << "\nSkriv in ditt användarnamn: ";
        std::cin >> username; 

        for(int i = 0; i < 3; i++)
            {
                if (username == customer[i].getUsername())
                {
                    isValidUsername = true;
                    return i; 
                }
            }

        if (!isValidUsername)
        {
            std::cout << "\nDitt username stämmer inte överens med någon av de registrerade användarna, försök igen.";
        }
    }
}

int main()
{
    bool continueProgram = true;
    std::string username;
    int user;
    Customer customer[3];

    customer[0].setUserInfo("melker", "lösen");
    customer[1].setUserInfo("henrik", "lösen2");
    customer[2].setUserInfo("karl", "lösen3");

    // customer[0].printCustomerInfo();
    
    user = inputUsername(customer);
        
        if (!customer[user].InputValidPassword())
        {   

            continueProgram = false; 
            break;
        }
        
        std::cout << "\nLog in successful";
        customer[user].printCustomerInfo();

        customer[user].addAccount();

        customer[user].printCustomerInfo();

       



    
    


   
}