#pragma region headers

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#pragma endregion

using namespace std;

class LibraryManager{
    /*  
    * @brief Simple implementation of the library manager.

    * This program provides the following functionalities to the user.
    * -> Add books to the library.
    * -> Remove books from the library
    * -> Edit the books in the library
    * -> Display the books in the library
    * -> Save the books in the library
    * 
    * @return void
    */
    private:
        string book_name;
        std::vector<string> books;
        int NUMBER_OF_BOOKS = 0;
        const string books_txt = "books.txt";

        void load_books(){
            ifstream file(books_txt);
            if(!file.is_open()){
                cerr << "Error opening the file!";
                return;
                
            }
            string line;
            while(getline(file, line)){
                books.push_back(line);
                NUMBER_OF_BOOKS++;
            }
            file.close();
        }

    public:
        LibraryManager(){
            load_books();
        };
    
        void main(){
            while (true){
                int choice;
                cout<< "----------------------------------------------------------------\n"
                    << "---------------- WellCome To The Library Manager----------------\n" 
                    << "----------------------What you want to do?----------------------\n"
                    << "-------------------------1.Add Books----------------------------\n"
                    << "------------------------2.Delete Books--------------------------\n"
                    << "------------------------3.Display Books-------------------------\n"
                    << "------------------------4.Update Books--------------------------\n"
                    << "-------------------------5.Save books---------------------------\n"
                    << "----------------------------6.Exit------------------------------\n"
                    << "----------------------------------------------------------------\n"
                    << endl <<">";
                cin >> choice;
                switch(choice){
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
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        return;
                    default:
                        cout << "Invalid Choice!\nExiting in 2 seconds..." << endl;
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        return;
                    }
            }    
        }

        #pragma region Helper functions

        void add_books(){

            try{
                while(true){
                    cout << "Please enter the name of the book..." << endl;
                    cin.ignore();
                    getline(cin, book_name);
                    
                    books.push_back(book_name);

                    std::this_thread::sleep_for(std::chrono::seconds(1));

                    cout << "\"" << book_name << "\"" << " added successfully..." << endl;
                    NUMBER_OF_BOOKS++;

                    char again;
                    cout << "Type (y) to add again and anything else to go back!" << endl;
                    cin >> again;

                    if(again == 'y'){continue;}
                    else{break;}
                }
            }
            catch(const std::exception& e){
                cerr << e.what() << '\n';
            }
        }

        void save_books() {
            if(books.empty()){
                cout << "No books entered to save!" << endl;
                return;
            }
            try{
                ofstream file(books_txt);
                if (!file.is_open()){
                    cerr << "Unable to open file";
                    return;
                }
                else{
                    for(auto &book : books){
                        file << book << endl;
                    }
                    file.close();
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "Books saved successfully!" << endl;
                }
            }
            catch(const std::exception& e){
                cerr << e.what() << '\n';
            }
            cout << "Returning to main menu..." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        void delete_books(){
            try{
                if(books.empty()){
                cout << "No books in the library..." << endl;
                return;
                }
                cout << "Please enter the name of the book you want to delete..." << endl;
                cin.ignore();
                getline(cin, book_name);

                bool found = false;
                for(int i = 0; i < books.size(); i++){
                    if(book_name == books[i]){
                        books.erase(books.begin() + i);
                        NUMBER_OF_BOOKS--;
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        cout << "\"" <<book_name << "\"" << " deleted successfully..." << endl;
                        found = true;
                        break;
                    }
                }
                if(!found){
                    cout << "Book not found..." << endl;
                    return;
                }
            }
            catch(const std::exception& e){
                cerr << e.what() << '\n';
            }
            cout << "Returning to main menu..." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));    
        }

        void display_books(){
            if(books.empty()){
                cout << "No books in the library..." << endl;
                return;
            }
            cout << "\nBooks in the library:" << endl;
            cout << "------------------------" << endl;
            for(const auto& book : books){
                cout << book << endl;
            }
            cout << "------------------------" << endl;
            cout << "\nReturning to main menu in 3 seconds..." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
                    
        }

        void update_books(){
            try{
                if(books.empty()){
                cout << "No books in the library..." << endl;
                return;
                }
                cout << "Please enter the name of the book you want to update..." << endl;
                cin.ignore();
                getline(cin, book_name);
                cout << "Enter the new name of the book..." << endl;
                string new_name;
                cin.ignore();
                getline(cin, new_name);

                bool found = false;

                for(int i = 0; i < books.size(); i++){
                    if(book_name == books[i]){
                        found = true;
                        books[i] = new_name;
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        cout << "\"" << book_name << "\"" << " updated successfully to " << "\"" << new_name << "\"" << endl;
                        break;
                    } 
                }
                if(!found){
                    cout << "Book not found..." << endl;
                    return;
                }
            }
            catch(const std::exception& e){
                cerr << e.what() << '\n';
            }
            cout << "Returning to main menu..." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        #pragma endregion
};

int main(){

    LibraryManager MyLibrary;
    MyLibrary.main();

    return 0;
}