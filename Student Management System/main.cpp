#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    string course;

    void addStudent() {
        ofstream file("students.txt", ios::app);

        cout << "\nEnter Student ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();

        cout << "Enter Course: ";
        getline(cin, course);

        file << id << "|" << name << "|" << age << "|" << course << endl;
        file.close();

        cout << "\nStudent Added Successfully!\n";
    }

    void displayStudents() {
        ifstream file("students.txt");

        string line;

        cout << "\n----- Student Records -----\n";

        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }

    void searchStudent() {
        ifstream file("students.txt");

        int searchId;
        string line;

        cout << "\nEnter Student ID to Search: ";
        cin >> searchId;

        bool found = false;

        while (getline(file, line)) {
            int pos = line.find("|");
            int id = stoi(line.substr(0, pos));

            if (id == searchId) {
                cout << "\nRecord Found:\n";
                cout << line << endl;
                found = true;
                break;
            }
        }

        if (!found)
            cout << "\nStudent Not Found!\n";

        file.close();
    }

    void updateStudent() {
        ifstream file("students.txt");
        ofstream temp("temp.txt");

        int updateId;
        string line;

        cout << "\nEnter Student ID to Update: ";
        cin >> updateId;
        cin.ignore();

        bool found = false;

        while (getline(file, line)) {
            int pos = line.find("|");
            int id = stoi(line.substr(0, pos));

            if (id == updateId) {
                found = true;

                string newName, newCourse;
                int newAge;

                cout << "Enter New Name: ";
                getline(cin, newName);

                cout << "Enter New Age: ";
                cin >> newAge;
                cin.ignore();

                cout << "Enter New Course: ";
                getline(cin, newCourse);

                temp << updateId << "|"
                     << newName << "|"
                     << newAge << "|"
                     << newCourse << endl;
            } else {
                temp << line << endl;
            }
        }

        file.close();
        temp.close();

        remove("students.txt");
        rename("temp.txt", "students.txt");

        if (found)
            cout << "\nStudent Updated Successfully!\n";
        else
            cout << "\nStudent Not Found!\n";
    }

    void deleteStudent() {
        ifstream file("students.txt");
        ofstream temp("temp.txt");

        int deleteId;
        string line;

        cout << "\nEnter Student ID to Delete: ";
        cin >> deleteId;

        bool found = false;

        while (getline(file, line)) {
            int pos = line.find("|");
            int id = stoi(line.substr(0, pos));

            if (id == deleteId) {
                found = true;
                continue;
            }

            temp << line << endl;
        }

        file.close();
        temp.close();

        remove("students.txt");
        rename("temp.txt", "students.txt");

        if (found)
            cout << "\nStudent Deleted Successfully!\n";
        else
            cout << "\nStudent Not Found!\n";
    }
};

int main() {
    Student s;
    int choice;

    do {
        cout << "\n==============================";
        cout << "\n STUDENT MANAGEMENT SYSTEM";
        cout << "\n==============================";
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            s.addStudent();
            break;

        case 2:
            s.displayStudents();
            break;

        case 3:
            s.searchStudent();
            break;

        case 4:
            s.updateStudent();
            break;

        case 5:
            s.deleteStudent();
            break;

        case 6:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}
