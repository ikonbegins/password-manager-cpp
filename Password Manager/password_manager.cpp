#include "password_manager.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

bool setupMasterPassword(){
    ifstream checkFile("master.txt");
    if (checkFile.good()){
        // master password already exists
        checkFile.close();
        return true;
    }

    string master;
    cout <<"\n[Setup] No master password found. Create one now: ";
    cin >> master;

    ofstream file("master.txt");
    if (file.is_open()){
        file << encrypt(master);
        file.close();
        cout << "\n[System] Master password set successfully!\n";
        return true;
    } else {
        cerr <<"\nError: Could not create master password file.\n";
        return false;
    }
}

bool verifyMasterPassword() {
    ifstream file ("master.txt");
    if(!file.is_open()){
        cerr << "\n[Error] Master password file missing. \n";
        return false;
    }

    string storedEncrypted;
    getline(file, storedEncrypted);
    file.close();

    string input;
    cout << "\nEnter master password: ";
    cin >> input;

    if (decrypt(storedEncrypted) == input) {
        cout << "\n[Access Granted]\n";
        return true;
    } else {
        cerr << "\n[Access Denied] Incorrect master password. \n";
        return false;
    }
}

//Simple Caesar Cipher encryption
string encrypt(const string& text) {
    string encrypted = text;
    for (char& c : encrypted){
        c = c + 3; //shifts each character by +3
    }

    return encrypted;
}

// Decryption (reverse of encryption)
string decrypt (const string& text){
    string decrypted = text;
    for (char& c : decrypted){
        c = c - 3; //shifts back by -3 to decrypt
    }
    return decrypted;
}

void displayMenu() {
    cout << "\n\n=== Password Manager ===";
    cout << "\n1) Add Password";
    cout << "\n2) View Passwords";
    cout << "\n3) Exit";
    cout << "\nEnter your choice: ";
}

void savePasswords(const string& site, const string& username, const string& password) {
    ofstream file("passwords.txt", ios::app);
    if (file.is_open()) {
        file << encrypt(site) << " " << encrypt(username) << " " << encrypt(password) << "\n";
        file.close();
        cout << "\nPassword saved successfully!";
    } else {
        cerr << "\nError: Unable to open file for writing.";
    }
}

void loadPasswords() {
    ifstream file("passwords.txt");
    if (file.is_open()) {
        string site, username, password;
        cout << "\nSaved Passwords:";
        while (file >> site >> username >> password) {
            cout << "\nSite: " << decrypt(site) << " | Username: " << decrypt(username) << " | Password: " << decrypt(password) << "\n";
        }
        file.close();
    } else {
        cerr << "\n[System] No passwords saved yet.\n";
    }
}