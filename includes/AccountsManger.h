#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Accounts.h"
#include "LibraryManager.h"

using namespace std;

class AccountManager {
private:
    const string filename = "data/accounts.txt";
    vector<Accounts> accounts;
    
    void load_accounts_from_file();
    void save_accounts_to_file();

public:
    AccountManager();
    void main_menu();
    void sign_up();
    bool sign_in();
    void display_account_info();
    void delete_account();
};

#endif // ACCOUNTMANAGER_H
