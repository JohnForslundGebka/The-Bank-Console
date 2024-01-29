#ifndef THE_BANK_CONSOLE_CONVERSIONRATE_H
#define THE_BANK_CONSOLE_CONVERSIONRATE_H

//Functions that opens the database and gets the conversion rates based on the input strings in the function
double getConversionRate(const std::string& fromCurrency, const std::string& toCurrency)
{

    //open database
    SQLite::Database db("bankDatabase.db");

    //create query
    SQLite::Statement query(db, "SELECT * FROM currency_rates WHERE currency_from = '"+fromCurrency+"' AND currency_to = '"+toCurrency+"'");

    try
    {
        while (query.executeStep())
        {
            return query.getColumn(2);   //get currency rate from the database
        }
    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

#endif //THE_BANK_CONSOLE_CONVERSIONRATE_H
