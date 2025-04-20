#include "sqldriver.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cctype>


/// Initialize connection to database
bool SqlDriver::InitConnection(){

    // Get users credentials
    setCredentials();
    // Check for validity
    try {
        // Create a driver instance
        driver = sql::mysql::get_mysql_driver_instance();

        // Connect to the local database
        con = driver->connect("tcp://localhost:3306", USERNAME, PASSWORD);

    }
    catch (...) {
        std::cout << "Error: " <<  "Could not connect to database. Incorrect username or password." << std::endl;
        return false;
    }

    // If connected to the database successfully
    if (con->isValid()){

        stmt = con->createStatement();

        try{
            std::cout << "Connecting...." << std::endl;
            con->setSchema("Inventory");
            std::cout << "Connected to the database Inventory Successfully!" << std::endl;
            return true;
        }

        //  Create a new database and table if it does not exists
        catch(...){
            stmt->execute("CREATE DATABASE Inventory");
            con->setSchema("Inventory");
            std::cout << "Creating table...." << std::endl;
            stmt->execute("CREATE TABLE Items(ItemId int NOT NULL AUTO_INCREMENT, Name varchar(255) NOT NULL, Quantity int NOT NULL, Price double NOT NULL, PRIMARY KEY(ItemId), UNIQUE (Name));");
            std::cout << "Database Inventory and Table Items created successfully!" << std::endl;
        }

    }
    return true;
}

/// Gets credential from user
void SqlDriver::setCredentials(){
    std::cout << "Enter username: ";
    std::cin >> USERNAME;
    std::cout << "Enter password: ";
    std::cin >> PASSWORD;
}


/// Main Menu of the application
void SqlDriver::mainMenu(){

    bool quit = false;
    bool validInput = false;
    std::string menuChoice = "";

    // Connnect to database until connection successful
    while(!InitConnection()){
    }

    // Main loop
    while(!quit){
        std::cout << std::endl;
        std::cout << "1. Display Items" << std::endl;
        std::cout << "2. Create Item" << std::endl;
        std::cout << "3. Update Item" << std::endl;
        std::cout << "4. Delete Item" << std::endl;
        std::cout << "5. Quit" << std::endl;


        std::cout << "\n\nEnter choice: ";
        std::cin >> menuChoice;
        std::cout << std::endl;

        // Validate input
        validInput = validateInput(menuChoice);

        // If input is number
        if(validInput){
            // Convert input into int
            int num = std::stoi(menuChoice);
            switch(num){
                case 1: displayItems();
                        break;
                case 2: createItem();
                        break;
                case 3: updateItem();
                        break;
                case 4: deleteItem();
                        break;
                case 5: quitApplication();
                        quit = true;
                        break;
                default: std::cout << "Incorrect choice!" << std::endl;
                        break;
            }
        }
        else{
            std::cout << "Invalid choice!" << std::endl;
            std::cin.clear();
            menuChoice = "";
        }
    }

}


/// Display the items in the database
void SqlDriver::displayItems(){
        // Get items from table
        res = stmt->executeQuery("SELECT * FROM Items");

        std::cout << std::setw(27) << std::left << "Name " << std::setw(17) << std::left << "Quantity" <<  "Price" << std::endl;
        std::cout << std::setfill('-') << std::setw(50) << "-" << std::endl;
        std::cout << std::setfill(' '); // Reset the fill

        // Loop items and display them
        while(res->next()){
            std::cout << std::setw(30) << std::left << res->getString(2);
            std::cout << std::setw(15) << std::left << res->getInt(3);
            std::cout << "$" << res->getDouble(4) << std::endl;
        }
        std::cout << "-----------------------End------------------------" << std::endl;
}

/// Create a new item in the database
void SqlDriver::createItem(){

        // Get user input
        std::cout << "Enter name: ";
        std::cin >> name;
        std::cout << "Enter quantity: ";
        std::cin >> qty;
        std::cout << "Enter price: ";
        std::cin >> price;

        name = toLower(name);

        if(validateInput(qty)){
            std::string insertString = "INSERT INTO Items (Name, Quantity, Price) VALUES ('" + name + "'" +  ", " + qty + ", " + price + ");";

            try{
                stmt->execute(insertString);
                std::cout << "Success!!!" << std::endl;
            }
            catch(...){
                std::cout << "Item already exists" << std::endl;
            }
        }
        else{
            std::cout << "Invalid Input!" << std::endl;
        }
}

/// Update and item from the database
void SqlDriver::updateItem(){

    // Get user input
    std::cout << "Enter the name of the item you wish to update: ";
    std::cin >> name;
    std::cout << "Enter the new quantity: ";
    std::cin >> qty;
    std::cout << "Enter the new price: $";
    std::cin >> price;

    // Set name to lowercase
     name = toLower(name);

    if(validateInput(qty)){
        // create the statement
        std::string updateString = "UPDATE Items SET Quantity=" + qty + ", Price=" + price + " WHERE Name='" + name + "';";
        try{

            int updatedCount = stmt->executeUpdate(updateString);
            if(updatedCount < 1){
                std::cout << "Item does not exists!!!" << std::endl;
            }
            else{
                std::cout << "Success!!!" << std::endl;
            }
        }
        catch(...){
            std::cout << "Item does not exists!!!" << std::endl;
        }
    }
    else{
            std::cout << "Invalid Input!" << std::endl;
        }

}

/// Delete item from the database
void SqlDriver::deleteItem(){

    // Get user input
    std::cout << "Enter the name of item you wish to delete: ";
    std::cin >> name;

    std::string deleteString = "DELETE FROM Items WHERE Name= '" + name + "';";

    try{
        int itemCount = stmt->executeUpdate(deleteString);
        if(itemCount < 1){
            std::cout << "Item does not exists!!!" << std::endl;
        }
        else{
            std::cout << "Success!!!" << std::endl;
        }
    }
    catch(...){
        std::cout << "Error" << std::endl;
    }
}

/// Deletes the connection to free up memory, and exits the application
void SqlDriver::quitApplication(){

    std::cout << "Quitting...." << std::endl;
    delete con;
    delete stmt;
}


/// Converts string to lower case
std::string SqlDriver::toLower(std::string itemName){
    std::string lowerName = "";
    for(char letter : itemName){
        lowerName += tolower(letter);
    }
    return lowerName;
}

/// Validate if user input is digit
bool SqlDriver::validateInput(std::string str){
    bool result;

    for(char letter : str){

        // Check if the char is a digit
        if(isdigit(letter)){
            result = true;
        }
        else{
            result = false;
        }
    }

    return result;
}


