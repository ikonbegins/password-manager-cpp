#include "password_manager.h"
#include <iostream>
#include <limits>
using namespace std;

int main() {

    // step 1 check and verify master password
    if (!setupMasterPassword()) return 1;
    if (!verifyMasterPassword()) return 1;
    int choice;
    string site, username, password;

    do {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                cout << "\nEnter site name: ";
                cin >> site;
                cout << "Enter username: ";
                cin >> username;

                char genChoice;
                cout << "Do you want to generate a strong password automatically? (y/n): ";
                cin >> genChoice;

                if (genChoice == 'y' || genChoice == 'Y') {
                int length;
                cout << "Enter password length: ";
                cin >> length;

                if (cin.fail() || length <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                length = 12;
                }

                password = generatePassword(length);
                cout << "\n[Generated Password] " << password << "\n";
                } else {
                cout << "Enter password manually: ";
                cin >> password;
                }

                savePasswords(site, username, password);
                break;
                }
            case 2:
                loadPasswords();
                break;
            case 3:
                searchPassword();
                break;
            case 4: {
                int length;
                cout << "\nEnter password length: ";
                cin >> length;

                if (cin.fail() || length <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid length. Please enter a positive number.\n";
                break;
                }

                string generated = generatePassword(length);
                cout << "Generated Password: " << generated << "\n";
                break;
            }
            case 5:
                cout << "\nExiting...";
                break;
            default:
                cout << "\nInvalid choice. Please try again.";
        }

    } while (choice != 5);

    return 0;
}