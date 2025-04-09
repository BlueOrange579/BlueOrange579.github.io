#ifndef SQLDRIVER_H
#define SQLDRIVER_H

#include <iostream>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>


class SqlDriver{
    private:
    std::string USERNAME;
    std::string PASSWORD;
    std::string name = "";
    std::string qty = "";
    std::string price = "";

    // Variables to connect to database
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

    public:
    bool InitConnection();
    void quitApplication();
    void createItem();
    void updateItem();
    void deleteItem();
    void displayItems();
    void setCredentials();
    void mainMenu();
    bool validateInput(std::string);
    std::string toLower(std::string);
};

#endif // SQLDRIVER_H
