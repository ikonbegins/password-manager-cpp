#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <string>
using namespace std;

// Function declarations
void displayMenu();
void savePasswords(const string& site, const string& username, const string& password);
void loadPasswords();
void searchPassword();
string generatePassword(int length = 12);

// Encryption helpers
string encrypt(const string& text);
string decrypt(const string& text);

// Function for master password
bool setupMasterPassword();
bool verifyMasterPassword();

#endif