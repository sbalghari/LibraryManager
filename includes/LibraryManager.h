#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

class LibraryManager {
private:
    string book_name;
    vector<string> books;
    const string books_txt = "data/books.txt";
    string last_operation;
    string last_book_name;
    string last_new_name;

    void load_books();
    void save_books_to_file();

public:
    LibraryManager();
    void main();
    void add_books();
    void delete_books();
    void display_books();
    void update_books();
    void save_books();
    void search_books();
    void sort_books();
    void reload_books();
    void undo_last_operation();
    void display_statistics();
};

#endif // LIBRARYMANAGER_H
