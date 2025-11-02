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
            case 1:
                cout << "\nEnter site name: ";
                cin >> site;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                savePasswords(site, username, password);
                break;
            case 2:
                loadPasswords();
                break;
            case 3:
                cout << "\nExiting...";
                break;
            default:
                cout << "\nInvalid choice. Please try again.";
        }

    } while (choice != 3);

    return 0;
}