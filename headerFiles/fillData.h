#ifndef THE_BANK_CONSOLE_FILLDATA_H
#define THE_BANK_CONSOLE_FILLDATA_H

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

void fillData(User users[])
{
    // Open a database file
    SQLite::Database db("bankDatabase.db");
    //create a query for all the users
    SQLite::Statement query(db, "SELECT * FROM users");

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

    //Get data for the users accounts
    fillAccounts(users);
}

#endif //THE_BANK_CONSOLE_FILLDATA_H
