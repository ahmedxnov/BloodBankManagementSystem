#include <iostream>
#include <functional>
#include <string>
#include "BloodBank.h"
#include <vector>

using namespace std;

void clearConsole()
{
    // Function to clear the console screen
    system("cls");
}

void printDonorMenu()
{
    // Function to print the donor menu
    cout << "+------------------------+\n";
    cout << "|   --- Donor Menu ---   |\n";
    cout << "|------------------------|\n";
    cout << "| 1. Login as a donor    |\n";
    cout << "| 2. Sign up as a donor  |\n";
    cout << "| 3. Exit                |\n";
    cout << "+------------------------+\n";
}

void printRecipientMenu()
{
    // Function to print the recipient menu
    cout << "+---------------------------+\n";
    cout << "| --- Recipient Menu ---    |\n";
    cout << "|---------------------------|\n";
    cout << "| 1. Login as a recipient   |\n";
    cout << "| 2. Sign up as a recipient |\n";
    cout << "| 3. Exit                   |\n";
    cout << "+---------------------------+\n";
}

void printDonorLoggedInMenu()
{
    // Function to print the logged-in donor menu
    cout << "+------------------------+\n";
    cout << "|   --- Donor Menu ---   |\n";
    cout << "|------------------------|\n";
    cout << "| 1. Donation request    |\n";
    cout << "| 2. Update your data    |\n";
    cout << "| 3. Logout              |\n";
    cout << "| 4. Delete your account |\n";
    cout << "+------------------------+\n";
}

void printRecipientLoggedInMenu()
{
    // Function to print the logged-in recipient menu
    cout << "+------------------------------------+\n";
    cout << "|        --- Recipient Menu ---       |\n";
    cout << "|------------------------------------|\n";
    cout << "| 1. Update your data                 |\n";
    cout << "| 2. Display all available blood data |\n";
    cout << "| 3. Request blood                    |\n";
    cout << "| 4. Logout                           |\n";
    cout << "| 5. Delete your account              |\n";
    cout << "+------------------------------------+\n";
}

void printOptionsMenu()
{
    // Function to print the options menu
    cout << "Do you want to do something else? (y/n): ";
}

int main()
{
    bool flag = true;
    char opt;

    while (flag) {
        BloodBank b;
        int option;
        string ssn, name, mail, password, gender, bloodType, lastDonationDate, Hospital, Doctor;
        vector<string> diseases;

        cout << "----- Welcome to the Blood Bank -----\n";
        cout << "1. For a donor\n";
        cout << "2. For a recipient\n";
        cout << "3. Exit\n";
        cin >> option;

        switch (option) {
        case 1: {
            clearConsole();
            printDonorMenu();
            cin >> option;

            if (option == 1) {
                clearConsole();
                cout << "----- Login as a donor -----\n";
                cout << "Enter your SSN: ";
                cin >> ssn;
                cout << "Enter your password: ";
                cin >> password;

                if (b.Personlogin(ssn, password, "donor")) {
                    clearConsole();
                    cout << "Login Successful.\n";

                    do {
                        b.printPersonData("donor");
                        cout << "\n";
                        printDonorLoggedInMenu();
                        cout << "Enter a number: ";
                        cin >> option;

                        clearConsole(); // Clear console after choosing an option

                        switch (option) {
                        case 1:
                            b.requestAdonation();
                            break;
                        case 2:
                            b.updatePersonData("donor");
                            break;
                        case 3:
                            option = 0; // Reset option to go back to the main menu
                            break;
                        case 4:
                            b.deletePersonData("donor");
                            option = 0; // Reset option to go back to the main menu
                            break;
                        }

                        if (option > 0 && option < 3) {
                            printOptionsMenu();
                            cin >> opt;

                            if (opt == 'y') {
                                clearConsole();
                            }
                            else {
                                option = 0; // Reset option to go back to the main menu
                            }
                        }
                    } while (option > 0);
                }
            }
            else {
                cout << "Enter your SSN: ";
                cin >> ssn;
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter your password: ";
                cin >> password;
                cout << "Enter your mail: ";
                cin >> mail;
                cout << "Enter your gender: ";
                cin >> gender;
                cout << "Enter your blood type: ";
                cin >> bloodType;

                cout << "Have you ever donated before? (y/n): ";
                char c;
                cin >> c;

                if (c == 'y') {
                    cout << "Enter your last donation date: ";
                    cin >> lastDonationDate;
                }
                else {
                    lastDonationDate = "";
                }

                cout << "Enter the number of diseases: ";
                int num;
                cin >> num;

                string disease;
                for (int i = 0; i < num; i++) {
                    disease = "";
                    cout << "Enter disease number " << i + 1 << ": ";
                    cin >> disease;
                    diseases.push_back(disease);
                }

                Donor d(ssn, name, mail, password, gender, bloodType, lastDonationDate, diseases);
                b.addPersonData(&d);

                clearConsole(); // Clear console after signing up
            }
            break;
        }
        case 2: {
            clearConsole();
            printRecipientMenu();
            cin >> option;

            if (option == 1) {
                cout << "----- Login as a recipient -----\n";
                cout << "Enter your SSN: ";
                cin >> ssn;
                cout << "Enter your password: ";
                cin >> password;

                if (b.Personlogin(ssn, password, "recipient")) {
                    clearConsole();
                    cout << "Login Successful.\n";

                    do {
                        b.printPersonData("recipient");
                        cout << "\n";
                        printRecipientLoggedInMenu();
                        cout << "Enter a number: ";
                        cin >> option;

                        clearConsole(); // Clear console after choosing an option

                        switch (option) {
                        case 1:
                            b.updatePersonData("recipient");
                            break;
                        case 2:
                            b.displayBloodData();
                            break;
                        case 3:
                            b.requestBlood();
                            break;
                        case 4:
                            option = 0; // Reset option to go back to the main menu
                            break;
                        case 5:
                            b.deletePersonData("recipient");
                            option = 0; // Reset option to go back to the main menu
                            break;
                        }

                        if (option > 0 && option < 4) {
                            printOptionsMenu();
                            cin >> opt;

                            if (opt == 'y') {
                                clearConsole();
                            }
                            else {
                                option = 0; // Reset option to go back to the main menu
                            }
                        }
                    } while (option > 0);
                }
            }
            else {
                cout << "Enter your SSN: ";
                cin >> ssn;
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter your password: ";
                cin >> password;
                cout << "Enter your mail: ";
                cin >> mail;
                cout << "Enter your gender: ";
                cin >> gender;
                cout << "Enter your blood type: ";
                cin >> bloodType;
                cout << "Enter the hospital name: ";
                cin.ignore();
                getline(cin, Hospital);
                cout << "Enter your doctor's name: ";
                cin.ignore();
                getline(cin, Doctor);

                Recipient r(ssn, name, mail, password,gender,bloodType, Hospital, Doctor);
                b.addPersonData(&r);

                clearConsole(); // Clear console after signing up
            }
            break;
        }
        case 3:
            flag = false;
            break;
        }
    }

    return 0;
}