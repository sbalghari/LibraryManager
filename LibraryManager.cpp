#include<iostream>
#include<vector>

using namespace std;

string BOOK_NAME;
std::vector<string> books;
int NUMBER_OF_BOOKS;

void add_books(){

    while(true){    
        cout << "Please enter the name of the book..." << endl;
        cin >> BOOK_NAME;
        
        books.push_back(BOOK_NAME);

        cout << BOOK_NAME << " added successfully..." << endl;
        NUMBER_OF_BOOKS++;

        char again;
        cout << "Type \(y\) to add again and anything else to exit!" << endl;
        cin >> again;

        if(again == 'y'){
            continue;
        }
        else{
            break;
        }
        
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

void main_menu(){

    int choice;


cout << "WellCome To The Library\n" << "\n"
     << "What do you want to...\n" 
     << "1.Add Books\n"
     << "2.Delete Books\n"
     << "3.Display Books\n"
     << "4.Exit\n"
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
        exit(0);
        break;
    default:
        cout << "Invalid Choice" << endl;
        break;
}
}

int main (){

    main_menu();

    return 0;
}