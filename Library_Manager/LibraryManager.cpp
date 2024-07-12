#include<iostream>
#include<vector>

#pragma region main

using namespace std;

string BOOK_NAME;
std::vector<string> books;
int NUMBER_OF_BOOKS;

void add_books(){

    try{
        while(true){    
            cout << "Please enter the name of the book..." << endl;
            cin >> BOOK_NAME;
            
            books.push_back(BOOK_NAME);

            cout << BOOK_NAME << " added successfully..." << endl;
            NUMBER_OF_BOOKS++;

            char again;
            cout << "Type (y) to add again and anything else to exit!" << endl;
            cin >> again;

            if(again == 'y'){
                continue;
            }
            else{
                break;
            }
        }
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
    
}

void delete_books(){
    cout << "Please enter the name of the book you want to delete..." << endl;
    cin >> BOOK_NAME;

    for(int i = 0; i < books.size(); i++){
        if(BOOK_NAME == books[i]){
            books.erase(books.begin() + i);
            NUMBER_OF_BOOKS--;
            cout << BOOK_NAME << " deleted successfully..." << endl;
            break;
        }
        else{
            cout << "Book not found..." << endl;
            break;
        }
    }

}

void display_books(){
    for(int i = 0; i < books.size(); i++){
        cout << books[i] << endl;
    }
}

void update_books(){

    cout << "Please enter the name of the book you want to update..." << endl;
    cin >> BOOK_NAME;
    cout << "Enter the new name of the book..." << endl;
    string new_name;
    cin >> new_name;

    for(int i = 0; i < books.size(); i++){
        if(BOOK_NAME == books[i]){
            books[i] = new_name;
            cout << BOOK_NAME << " updated successfully to " << new_name << endl;
            break;
        }
        else{
            cout << "Book not found..." << endl;
            break;
        }
    }
    
}

int main (){

    int choice;
    cout << "WellCome To The Library\n" << "\n"
        << "What do you want to...\n" 
        << "1.Add Books\n"
        << "2.Delete Books\n"
        << "3.Display Books\n"
        << "4.Update Books\n"
        << "5.Exit\n"
        << endl;

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
            exit(0);
            break;
        default:
            cout << "Invalid Choice" << endl;
            break;
    }
    return 0;
}

#pragma endregion
