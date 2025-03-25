#include "Accounts.h"

Accounts::Accounts(string accname, string accpass)
    : account_username(accname), account_password(accpass) {}

void Accounts::set_account_username(const string& accname) {
    account_username = accname;
}

void Accounts::set_account_password(const string& accpass) {
    account_password = accpass;
}

void Accounts::display_account_info(){
    cout << "Username: " << account_username << endl;
    cout << "Password: " << account_password << endl;
}
