#pragma region headers
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <thread>
#include <chrono>
#pragma endregion

using namespace std;

class LibraryManager {
    private:

    string book_name;
    vector<string> books;
    const string books_txt = "books.txt";
    string last_operation;
    string last_book_name;
    string last_new_name;

    void load_books() {
        ifstream file(books_txt);
        if (!file.is_open()) {
            cerr << "Error opening the file!" << endl;
            return;
        }
        string line;
        while (getline(file, line)) {
            books.push_back(line);
        }
        file.close();
    }

    void save_books_to_file() {
        ofstream file(books_txt);
        if (!file.is_open()) {
            cerr << "Unable to open file!" << endl;
            return;
        }
        for (const auto& book : books) {
            file << book << endl;
        }
        cout << "Books saved successfully!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        file.close();
    }

    public:

    LibraryManager() {
        load_books();
    }

    void main() {
        while (true) {
            int choice;
            cout << "****************************************************************\n"
                    << "*                                                              *\n"
                    << "*               Welcome To The Library Manager                 *\n"
                    << "*                                                              *\n"
                    << "****************************************************************\n"
                    << "*                                                              *\n"
                    << "*                   What would you like to do?                 *\n"
                    << "*                                                              *\n"
                    << "*    1. Add Books                                              *\n"
                    << "*    2. Delete Books                                           *\n"
                    << "*    3. Display Books                                          *\n"
                    << "*    4. Update Books                                           *\n"
                    << "*    5. Save Books                                             *\n"
                    << "*    6. Search Books                                           *\n"
                    << "*    7. Sort Books                                             *\n"
                    << "*    8. Reload Books From File                                 *\n"
                    << "*    9. Undo Last Operation                                    *\n"
                    << "*    10. Display Statistics                                    *\n"
                    << "*    11. Exit the Program                                      *\n"
                    << "*                                                              *\n"
                    << "****************************************************************\n"
                    << endl << "> ";

            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number." << endl;
                continue;
            }
            cin.ignore();
            switch (choice) {
                case 1:
                    add_books();
                    break;
                case 2:
                    delete_books();
                    break;
                case 3:
                    display_books();
                    break;
                case 4:
                    update_books();
                    break;
                case 5:
                    save_books();
                    break;
                case 6:
                    search_books();
                    break;
                case 7:
                    sort_books();
                    break;
                case 8:
                    reload_books();
                    break;
                case 9:
                    undo_last_operation();
                    break;
                case 10:
                    display_statistics();
                    break;
                case 11:
                    cout << "\nExiting...\n";
                    return;
                default:
                    cout << "Invalid choice! Please enter a number between 1 and 11." << endl;
            }
        }
    }

#pragma region Helper functions

    void add_books() {
        while (true) {
            cout << "Please enter the name of the book:" << endl;
            getline(cin, book_name);
            if (book_name.empty()) {
                cout << "Book name cannot be empty! Please try again." << endl;
                continue;
            }
            books.push_back(book_name);
            last_operation = "add";
            last_book_name = book_name;
            cout << "\"" << book_name << "\" added successfully." << endl;
            this_thread::sleep_for(chrono::seconds(1));

            char query;
            cout << "Type 'y' to add another book, or anything else to go back." << endl;
            cin >> query;
            cin.ignore();
            if (query != 'y') {
                break;
            }
        }
    }

    void save_books() {
        if (books.empty()) {
            cout << "No books to save!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            return;
        }
        save_books_to_file();
    }

    void delete_books() {
        if (books.empty()) {
            cout << "No books in the library!" << endl;
            return;
        }
        cout << "Please enter the name of the book you want to delete:" << endl;
        getline(cin, book_name);

        auto it = find(books.begin(), books.end(), book_name);
        if (it != books.end()) {
            books.erase(it);
            last_operation = "delete";
            last_book_name = book_name;
            cout << "\"" << book_name << "\" deleted successfully." << endl;
        } else {
            cout << "Book not found!" << endl;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }

    void display_books() {
        if (books.empty()) {
            cout << "No books in the library!" << endl;
            return;
        }
        cout << "\nBooks in the library:" << endl;
        cout << "------------------------" << endl;
        for (const auto& book : books) {
            cout << book << endl;
        }
        cout << "------------------------" << endl;
        cout << "\nReturning to main menu..." << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }

    void update_books() {
        if (books.empty()) {
            cout << "No books in the library!" << endl;
            return;
        }
        cout << "Please enter the name of the book you want to update:" << endl;
        getline(cin, book_name);
        cout << "Enter the new name of the book:" << endl;
        string new_name;
        getline(cin, new_name);
        if (new_name.empty()) {
            cout << "New book name cannot be empty! Please try again." << endl;
            return;
        }

        auto it = find(books.begin(), books.end(), book_name);
        if (it != books.end()) {
            last_operation = "update";
            last_book_name = book_name;
            last_new_name = new_name;
            *it = new_name;
            cout << "\"" << book_name << "\" updated successfully to \"" << new_name << "\"." << endl;
        } else {
            cout << "Book not found!" << endl;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }

    void search_books() {
        cout << "Please enter the name of the book you want to search for:" << endl;
        getline(cin, book_name);
        auto it = find(books.begin(), books.end(), book_name);
        if (it != books.end()) {
            cout << "Book \"" << book_name << "\" found in the library." << endl;
        } else {
            cout << "Book not found!" << endl;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }

    void sort_books() {
        sort(books.begin(), books.end());
        cout << "Books sorted alphabetically." << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    void reload_books() {
        books.clear();
        load_books();
        cout << "Books reloaded from the file." << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    void undo_last_operation() {
        if (last_operation.empty()) {
            cout << "No operations to undo!" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            return;
        }
        if (last_operation == "add") {
            auto it = find(books.begin(), books.end(), last_book_name);
            if (it != books.end()) {
                books.erase(it);
                cout << "Undo successful: \"" << last_book_name << "\" has been removed." << endl;
            }
        } else if (last_operation == "delete") {
            books.push_back(last_book_name);
            cout << "Undo successful: \"" << last_book_name << "\" has been restored." << endl;
        } else if (last_operation == "update") {
            auto it = find(books.begin(), books.end(), last_new_name);
            if (it != books.end()) {
                *it = last_book_name;
                cout << "Undo successful: \"" << last_new_name << "\" has been reverted to \"" << last_book_name << "\"." << endl;
            }
        }
        last_operation.clear();
        this_thread::sleep_for(chrono::seconds(1));
    }

    void display_statistics() {
        cout << "Total number of books: " << books.size() << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    #pragma endregion
};


class Accounts {

    public:

    string account_username;
    string account_password;

    Accounts(string accname, string accpass)
        : account_username(accname), account_password(accpass) {}
    
    void set_account_username(const string& accname) {
        account_username = accname;
    }

    void set_account_password(const string& accpass) {
        account_password = accpass;
    }

    void display_account_info(){
        cout << "Username: " << account_username << endl;
        cout << "Password: " << account_password << endl;
    }
};


class AccountManagement {
    private:
    const string filename = "accounts.txt";

    void load_accounts_from_file(){
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
    void save_accounts_to_file(){
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

    public:

    vector<Accounts> accounts;

    AccountManagement() {
        load_accounts_from_file();
        }

    void main_menu() {
        int choice;
        while(true) {
            cout << "\n--- Main Menu ---" << endl;
            cout << "1. Sign Up" << endl;
            cout << "2. Sign In" << endl;
            cout << "3. Save Account" << endl;
            cout << "4. Delete Account" << endl;
            cout << "5. Display Accounts" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch(choice) {
                case 1:
                    sign_up();
                    break;
                case 2:
                    if(sign_in()) {
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
    
    void sign_up() {
        string username, password;
        cout << "Enter a username: ";
        cin >> username;

        for (auto& acc : accounts) {
            if(acc.account_username == username) {
                cout << "Username already exists. Please choose a different one." << endl;
                return;
            }
        }

        cout << "Enter a password: ";
        cin >> password;

        accounts.push_back(Accounts(username, password));
        cout << "Account created successfully." << endl;
    
    }

    bool sign_in(){
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
                if(acc.account_password == password){
                    cout << "Sign in successful." << endl;
                    return true;
                }
                else{
                    cout << "Invalid password." << endl;
                    return false;
                }
            }
            else{
                cout << "Invalid username." << endl;
                return false;
            }
            
            cout << "Invalid username or password." << endl;
            return false;
            
        }
    }

    void display_account_info() {
        if(accounts.empty()) {
            cout <<"No accounts!" << endl;
            return;
        }
        for (auto& acc : accounts) {
                cout << "-----------------------------" << endl;
                acc.display_account_info();
                cout << "-----------------------------" << endl;
        }
    }

    void delete_account() {
        if(accounts.empty()) {
            cout <<"No accounts!" << endl;
            return;
        }
        string username;

        cout << "Enter the username of the account to delete: " << endl;
        cin >> username;

        for (auto it = accounts.begin(); it!= accounts.end(); ++it) {
            if (it->account_username == username) {
                accounts.erase(it);
                cout << "Account deleted successfully." << endl;
                return;
            }
        }
        cout << "Account not found." << endl;
    }
};

int main() {
    AccountManagement account_manager;
    account_manager.main_menu();
}