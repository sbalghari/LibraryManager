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

    This program provides the following functionalities to the user:
    -> Add books to the library.
    -> Remove books from the library.
    -> Edit the books in the library.
    -> Display the books in the library.
    -> Save the books in a text file.
    -> Search for a book by name.
    -> Sort the books alphabetically.
    -> Reload books from the text file.
    -> Undo the last add, delete, or update operation.
    -> Display statistics such as the total number of books.

    */
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

public:
    LibraryManager() {
        load_books();
    }

    void main() {
        while (true) {
            int choice;
            cout<< "****************************************************************\n"
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
        try {
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
            this_thread::sleep_for(chrono::seconds(1));
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
        } catch (const exception &e) {
            cerr << e.what() << '\n';
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
        for (const auto &book : books) {
            cout << book << endl;
        }
        cout << "------------------------" << endl;
        cout << "\nReturning to main menu..." << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }

    void update_books() {
        try {
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
        } catch (const exception &e) {
            cerr << e.what() << '\n';
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

int main() {
    LibraryManager MyLibrary;
    MyLibrary.main();
    return 0;
}
