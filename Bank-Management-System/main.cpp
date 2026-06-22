#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Bank {
public:
    int accNo;
    string name;
    double balance;

    void createAccount() {
        ofstream file("accounts.txt", ios::app);

        cout << "\nEnter Account Number: ";
        cin >> accNo;
        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, name);

        cout << "Enter Initial Balance: ";
        cin >> balance;

        file << accNo << "|" << name << "|" << balance << endl;
        file.close();

        cout << "\nAccount Created Successfully!\n";
    }

    void displayAccounts() {
        ifstream file("accounts.txt");
        string line;

        cout << "\n----- Account Records -----\n";

        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }

    void checkBalance() {
        ifstream file("accounts.txt");

        int searchAcc;
        string line;

        cout << "\nEnter Account Number: ";
        cin >> searchAcc;

        bool found = false;

        while (getline(file, line)) {
            int pos = line.find("|");
            int acc = stoi(line.substr(0, pos));

            if (acc == searchAcc) {
                cout << "\nAccount Found:\n";
                cout << line << endl;
                found = true;
                break;
            }
        }

        if (!found)
            cout << "\nAccount Not Found!\n";

        file.close();
    }

    void deposit() {
        ifstream file("accounts.txt");
        ofstream temp("temp.txt");

        int searchAcc;
        double amount;
        string line;

        cout << "\nEnter Account Number: ";
        cin >> searchAcc;

        cout << "Enter Deposit Amount: ";
        cin >> amount;

        bool found = false;

        while (getline(file, line)) {
            int p1 = line.find("|");
            int p2 = line.find("|", p1 + 1);

            int acc = stoi(line.substr(0, p1));
            string cname = line.substr(p1 + 1, p2 - p1 - 1);
            double bal = stod(line.substr(p2 + 1));

            if (acc == searchAcc) {
                bal += amount;
                found = true;
            }

            temp << acc << "|" << cname << "|" << bal << endl;
        }

        file.close();
        temp.close();

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");

        if (found)
            cout << "\nAmount Deposited Successfully!\n";
        else
            cout << "\nAccount Not Found!\n";
    }

    void withdraw() {
        ifstream file("accounts.txt");
        ofstream temp("temp.txt");

        int searchAcc;
        double amount;
        string line;

        cout << "\nEnter Account Number: ";
        cin >> searchAcc;

        cout << "Enter Withdrawal Amount: ";
        cin >> amount;

        bool found = false;

        while (getline(file, line)) {
            int p1 = line.find("|");
            int p2 = line.find("|", p1 + 1);

            int acc = stoi(line.substr(0, p1));
            string cname = line.substr(p1 + 1, p2 - p1 - 1);
            double bal = stod(line.substr(p2 + 1));

            if (acc == searchAcc) {
                found = true;

                if (amount <= bal) {
                    bal -= amount;
                    cout << "\nWithdrawal Successful!\n";
                } else {
                    cout << "\nInsufficient Balance!\n";
                }
            }

            temp << acc << "|" << cname << "|" << bal << endl;
        }

        file.close();
        temp.close();

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");

        if (!found)
            cout << "\nAccount Not Found!\n";
    }
};

int main() {
    Bank b;
    int choice;

    do {
        cout << "\n============================";
        cout << "\n BANK MANAGEMENT SYSTEM";
        cout << "\n============================";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Check Balance";
        cout << "\n5. Display Accounts";
        cout << "\n6. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            b.createAccount();
            break;

        case 2:
            b.deposit();
            break;

        case 3:
            b.withdraw();
            break;

        case 4:
            b.checkBalance();
            break;

        case 5:
            b.displayAccounts();
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
