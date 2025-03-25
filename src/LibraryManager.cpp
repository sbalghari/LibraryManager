#include "LibraryManager.h"

LibraryManager::LibraryManager() {
    load_books();
}

void LibraryManager::load_books() {
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

void LibraryManager::save_books_to_file() {
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

void LibraryManager::main() {
    while (true) {
        int choice;
        cout << "******** Welcome To The Library Manager ********\n";
        cout << "1. Add Books\n2. Delete Books\n3. Display Books\n4. Update Books\n";
        cout << "5. Save Books\n6. Search Books\n7. Sort Books\n8. Reload Books\n";
        cout << "9. Undo Last Operation\n10. Display Statistics\n11. Exit\n> ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: add_books(); break;
            case 2: delete_books(); break;
            case 3: display_books(); break;
            case 4: update_books(); break;
            case 5: save_books(); break;
            case 6: search_books(); break;
            case 7: sort_books(); break;
            case 8: reload_books(); break;
            case 9: undo_last_operation(); break;
            case 10: display_statistics(); break;
            case 11: cout << "\nExiting...\n"; return;
            default: cout << "Invalid choice! Please enter a valid number.\n";
        }
    }
}

void LibraryManager::add_books() {
    cout << "Enter book name: ";
    getline(cin, book_name);
    if (!book_name.empty()) {
        books.push_back(book_name);
        last_operation = "add";
        last_book_name = book_name;
        cout << "\"" << book_name << "\" added successfully." << endl;
    }
}

void LibraryManager::delete_books() {
    if (books.empty()) {
        cout << "No books in the library!" << endl;
        return;
    }
    cout << "Enter book name to delete: ";
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
}

void LibraryManager::display_books() {
    if (books.empty()) {
        cout << "No books in the library!" << endl;
        return;
    }
    cout << "Books in the library:\n";
    for (const auto& book : books) {
        cout << "- " << book << endl;
    }
}

void LibraryManager::update_books() {
    if (books.empty()) {
        cout << "No books in the library!" << endl;
        return;
    }
    cout << "Enter the book name to update: ";
    getline(cin, book_name);
    auto it = find(books.begin(), books.end(), book_name);
    if (it != books.end()) {
        cout << "Enter new book name: ";
        getline(cin, last_new_name);
        *it = last_new_name;
        last_operation = "update";
        last_book_name = book_name;
        cout << "Updated successfully!" << endl;
    } else {
        cout << "Book not found!" << endl;
    }
}

void LibraryManager::save_books() {
    save_books_to_file();
}

void LibraryManager::search_books() {
    cout << "Enter book name to search: ";
    getline(cin, book_name);
    auto it = find(books.begin(), books.end(), book_name);
    cout << (it != books.end() ? "Book found!" : "Book not found!") << endl;
}

void LibraryManager::sort_books() {
    sort(books.begin(), books.end());
    cout << "Books sorted successfully!" << endl;
}

void LibraryManager::reload_books() {
    books.clear();
    load_books();
    cout << "Books reloaded from file." << endl;
}

void LibraryManager::undo_last_operation() {
    if (last_operation.empty()) {
        cout << "No operations to undo!" << endl;
        return;
    }
    if (last_operation == "add") {
        books.pop_back();
        cout << "Undo add operation successful!" << endl;
    } else if (last_operation == "delete") {
        books.push_back(last_book_name);
        cout << "Undo delete operation successful!" << endl;
    } else if (last_operation == "update") {
        auto it = find(books.begin(), books.end(), last_new_name);
        if (it != books.end()) {
            *it = last_book_name;
            cout << "Undo update operation successful!" << endl;
        }
    }
    last_operation.clear();
}

void LibraryManager::display_statistics() {
    cout << "Total books: " << books.size() << endl;
}
