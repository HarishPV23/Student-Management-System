#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Library {
public:
    int bookId;
    string title;
    string author;
    string status;

    void addBook() {
        ofstream file("books.txt", ios::app);

        cout << "\nEnter Book ID: ";
        cin >> bookId;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        status = "Available";

        file << bookId << "|"
             << title << "|"
             << author << "|"
             << status << endl;

        file.close();

        cout << "\nBook Added Successfully!\n";
    }

    void displayBooks() {
        ifstream file("books.txt");

        string line;

        cout << "\n----- Book Records -----\n";

        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }

    void searchByTitle() {
        ifstream file("books.txt");

        string searchTitle;
        string line;

        cin.ignore();

        cout << "\nEnter Title to Search: ";
        getline(cin, searchTitle);

        bool found = false;

        while (getline(file, line)) {
            if (line.find(searchTitle) != string::npos) {
                cout << line << endl;
                found = true;
            }
        }

        if (!found)
            cout << "\nBook Not Found!\n";

        file.close();
    }

    void searchByAuthor() {
        ifstream file("books.txt");

        string searchAuthor;
        string line;

        cin.ignore();

        cout << "\nEnter Author Name: ";
        getline(cin, searchAuthor);

        bool found = false;

        while (getline(file, line)) {
            if (line.find(searchAuthor) != string::npos) {
                cout << line << endl;
                found = true;
            }
        }

        if (!found)
            cout << "\nBook Not Found!\n";

        file.close();
    }

    void issueBook() {
        ifstream file("books.txt");
        ofstream temp("temp.txt");

        int id;
        string line;

        cout << "\nEnter Book ID to Issue: ";
        cin >> id;

        bool found = false;

        while (getline(file, line)) {
            int p1 = line.find("|");
            int p2 = line.find("|", p1 + 1);
            int p3 = line.find("|", p2 + 1);

            int bookID = stoi(line.substr(0, p1));

            string title = line.substr(p1 + 1, p2 - p1 - 1);
            string author = line.substr(p2 + 1, p3 - p2 - 1);
            string status = line.substr(p3 + 1);

            if (bookID == id) {
                found = true;

                if (status == "Available") {
                    status = "Issued";
                    cout << "\nBook Issued Successfully!\n";
                } else {
                    cout << "\nBook Already Issued!\n";
                }
            }

            temp << bookID << "|"
                 << title << "|"
                 << author << "|"
                 << status << endl;
        }

        file.close();
        temp.close();

        remove("books.txt");
        rename("temp.txt", "books.txt");

        if (!found)
            cout << "\nBook Not Found!\n";
    }

    void returnBook() {
        ifstream file("books.txt");
        ofstream temp("temp.txt");

        int id;
        string line;

        cout << "\nEnter Book ID to Return: ";
        cin >> id;

        bool found = false;

        while (getline(file, line)) {
            int p1 = line.find("|");
            int p2 = line.find("|", p1 + 1);
            int p3 = line.find("|", p2 + 1);

            int bookID = stoi(line.substr(0, p1));

            string title = line.substr(p1 + 1, p2 - p1 - 1);
            string author = line.substr(p2 + 1, p3 - p2 - 1);
            string status = line.substr(p3 + 1);

            if (bookID == id) {
                found = true;

                if (status == "Issued") {
                    status = "Available";
                    cout << "\nBook Returned Successfully!\n";
                } else {
                    cout << "\nBook Already Available!\n";
                }
            }

            temp << bookID << "|"
                 << title << "|"
                 << author << "|"
                 << status << endl;
        }

        file.close();
        temp.close();

        remove("books.txt");
        rename("temp.txt", "books.txt");

        if (!found)
            cout << "\nBook Not Found!\n";
    }
};

int main() {
    Library lib;
    int choice;

    do {
        cout << "\n============================";
        cout << "\n LIBRARY MANAGEMENT SYSTEM";
        cout << "\n============================";
        cout << "\n1. Add Book";
        cout << "\n2. Display Books";
        cout << "\n3. Search By Title";
        cout << "\n4. Search By Author";
        cout << "\n5. Issue Book";
        cout << "\n6. Return Book";
        cout << "\n7. Exit";
        cout << "\nEnter Choice: ";

        cin >> choice;

        switch (choice) {
        case 1:
            lib.addBook();
            break;

        case 2:
            lib.displayBooks();
            break;

        case 3:
            lib.searchByTitle();
            break;

        case 4:
            lib.searchByAuthor();
            break;

        case 5:
            lib.issueBook();
            break;

        case 6:
            lib.returnBook();
            break;

        case 7:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}
