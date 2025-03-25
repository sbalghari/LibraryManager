#include "AccountsManger.h"

using namespace std;

AccountManager::AccountManager() {
    load_accounts_from_file();
}

void AccountManager::load_accounts_from_file() {
    ifstream file(filename);
    if (file.is_open()) {
        string username, password;
        while (getline(file, username, ',')) {
            getline(file, password);
            accounts.push_back(Accounts(username, password));
        }
        file.close();
    } else {
        cout << "Error opening file: " << filename << endl;
    }
}

void AccountManager::save_accounts_to_file() {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& acc : accounts) {
            file << acc.account_username << "," << acc.account_password << endl;
        }
        file.close();
    } else {
        cout << "Error opening file: " << filename << endl;
    }
}

void AccountManager::main_menu() {
    int choice;
    while (true) {
        cout << "\n--- Main Menu ---" << endl;
        cout << "1. Sign Up" << endl;
        cout << "2. Sign In" << endl;
        cout << "3. Save Account" << endl;
        cout << "4. Delete Account" << endl;
        cout << "5. Display Accounts" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                sign_up();
                break;
            case 2:
                if (sign_in()) {
                    LibraryManager lm;
                    lm.main();
                }
                break;
            case 3:
                save_accounts_to_file();
                break;
            case 4:
                delete_account();
                break;
            case 5:
                display_account_info();
                break;
            case 6:
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

void AccountManager::sign_up() {
    string username, password;
    cout << "Enter a username: ";
    cin >> username;

    for (auto& acc : accounts) {
        if (acc.account_username == username) {
            cout << "Username already exists. Please choose a different one." << endl;
            return;
        }
    }

    cout << "Enter a password: ";
    cin >> password;
    accounts.push_back(Accounts(username, password));
    cout << "Account created successfully." << endl;
}

bool AccountManager::sign_in() {
    if (accounts.empty()) {
        cout << "No accounts found. Please sign up first." << endl;
        return false;
    }

    string username, password;
    cout << "Enter username: ";
    cin >> username;

    for (auto& acc : accounts) {
        if (acc.account_username == username) {
            cout << "Enter password: ";
            cin >> password;
            if (acc.account_password == password) {
                cout << "Sign in successful." << endl;
                return true;
            } else {
                cout << "Invalid password." << endl;
                return false;
            }
        }
    }
    cout << "Invalid username." << endl;
    return false;
}

void AccountManager::display_account_info() {
    if (accounts.empty()) {
        cout << "No accounts!" << endl;
        return;
    }
    for (auto& acc : accounts) {
        cout << "-----------------------------" << endl;
        acc.display_account_info();
        cout << "-----------------------------" << endl;
    }
}

void AccountManager::delete_account() {
    if (accounts.empty()) {
        cout << "No accounts!" << endl;
        return;
    }

    string username;
    cout << "Enter the username of the account to delete: ";
    cin >> username;

    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if (it->account_username == username) {
            accounts.erase(it);
            cout << "Account deleted successfully." << endl;
            return;
        }
    }
    cout << "Account not found." << endl;
}
