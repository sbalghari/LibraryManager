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
    /*
    Simple implementation of a library management system.

    This program provides the following functionalities to the user.
    -> Add books to the library.
    -> Remove books from the library.
    -> Edit the books in the library.
    -> Display the books in the library.
    -> Save the books in a text file.

    */
private:
    string book_name;
    vector<string> books;
    const string books_txt = "books.txt";

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

public:
    LibraryManager() {
        load_books();
    }

    void main() {
        while (true) {
            int choice;
            cout << "----------------------------------------------------------------\n"
                 << "---------------- WellCome To The Library Manager----------------\n"
                 << "----------------------What you want to do?----------------------\n"
                 << "-------------------------1.Add Books----------------------------\n"
                 << "------------------------2.Delete Books--------------------------\n"
                 << "------------------------3.Display Books-------------------------\n"
                 << "------------------------4.Update Books--------------------------\n"
                 << "-------------------------5.Save books---------------------------\n"
                 << "----------------------------6.Exit------------------------------\n"
                 << "----------------------------------------------------------------\n"
                 << endl << ">";
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
                    cout << "\nExiting...\n";
                    return;
                default:
                    cout << "Invalid Choice! Please enter a number between 1 and 6." << endl;
            }
        }
    }

#pragma region Helper functions

    void add_books() {
        try {
            while (true) {
                cout << "Please enter the name of the book!" << endl;
                getline(cin, book_name);
                books.push_back(book_name);
                cout << "\"" << book_name << "\"" << " added successfully." << endl;

                char query;
                cout << "Type (y) to add another book, or anything else to go back!" << endl;
                cin >> query;
                cin.ignore();
                if (query != 'y') {
                    break;
                }
            }
        } catch (const exception &e) {
            cerr << e.what() << '\n';
        }
    }

    void save_books() {
        if (books.empty()) {
            cout << "No books to save!" << endl;
            return;
        }
        try {
            ofstream file(books_txt);
            if (!file.is_open()) {
                cerr << "Unable to open file!" << endl;
                return;
            }
            for (const auto &book : books) {
                file << book << endl;
            }
            cout << "Books saved successfully!" << endl;
            file.close();
        } catch (const exception &e) {
            cerr << e.what() << '\n';
        }
    }

    void delete_books() {
        try {
            if (books.empty()) {
                cout << "No books in the library!" << endl;
                return;
            }
            cout << "Please enter the name of the book you want to delete." << endl;
            getline(cin, book_name);

            auto it = find(books.begin(), books.end(), book_name);
            if (it != books.end()) {
                books.erase(it);
                cout << "\"" << book_name << "\"" << " deleted successfully." << endl;
            } else {
                cout << "Book not found!" << endl;
            }
        } catch (const exception &e) {
            cerr << e.what() << '\n';
        }
    }

    void display_books() {
        if (books.empty()) {
            cout << "No books in the library!" << endl;
            return;
        }
        cout << "\nBooks in the library:-" << endl;
        cout << "------------------------" << endl;
        for (const auto &book : books) {
            cout << book << endl;
        }
        cout << "------------------------" << endl;
        cout << "\nReturning to main menu..." << endl;
        this_thread::sleep_for(chrono::seconds(3));
    }

    void update_books() {
        try {
            if (books.empty()) {
                cout << "No books in the library!" << endl;
                return;
            }
            cout << "Please enter the name of the book you want to update." << endl;
            getline(cin, book_name);
            cout << "Enter the new name of the book." << endl;
            string new_name;
            getline(cin, new_name);

            auto it = find(books.begin(), books.end(), book_name);
            if (it != books.end()) {
                *it = new_name;
                cout << "\"" << book_name << "\"" << " updated successfully to " << "\"" << new_name << "\"" << endl;
            } else {
                cout << "Book not found!" << endl;
            }
        } catch (const exception &e) {
            cerr << e.what() << '\n';
        }
    }

#pragma endregion
};

int main() {
    LibraryManager MyLibrary;
    MyLibrary.main();
    return 0;
}
