#include<iostream>
#include<string>

using namespace std;

void add_books(){

    string book_name;

    cout << "Please enter the name of the book..." << endl;
    cin >> book_name;
    cout << book_name << " added successfully..." << endl;

}


void delete_books(){

}

void update_books(){

}

void search_books(){

}

void display_books(){

}

void main_menu(){

    int choice;

cout << "WellCome To The Library" 
     << "What do you want to..." 
     << "1.Add Books"
     << "2.Delete Books"
     << "3.Update Books"
     << "4.Search Books"
     << "5.Display Books"
     << "6.Exit"
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
        update_books();
        break;
    case 4:
        search_books();
        break;
    case 5:
        display_books();
        break;
    case 6:
        exit(0);
        break;
    default:
        cout << "Invalid Choice" << endl;
        break;
}
}

int main (){

    

    return 0;
}