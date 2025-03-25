#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include <iostream>
#include <string>

using namespace std;

class Accounts {
public:
    string account_username;
    string account_password;

    // Constructor declaration
    Accounts(string accname, string accpass);

    // Setter declarations
    void set_account_username(const string& accname);
    void set_account_password(const string& accpass);

    // Member function declaration to display account info
    void display_account_info();
};

#endif // ACCOUNTS_H
