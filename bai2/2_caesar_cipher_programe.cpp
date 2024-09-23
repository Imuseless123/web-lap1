#include <iostream>
#include <string>

using namespace std;

// Function to encrypt the plaintext using the Caesar cipher
string encryptCaesar(string plaintext, int key) {
    string result = "";

    // Traverse the plaintext character by character
    for (int i = 0; i < plaintext.length(); i++) {
        char c = plaintext[i];

        // Encrypt uppercase letters
        if (isupper(c)) {
            result += char(int(c + key - 65) % 26 + 65);
        }
        // Encrypt lowercase letters
        else if (islower(c)) {
            result += char(int(c + key - 97) % 26 + 97);
        }
        // If it's not an alphabetic character, keep it unchanged
        else {
            result += c;
        }
    }

    return result;
}

// Function to decrypt the ciphertext using the Caesar cipher
string decryptCaesar(string ciphertext, int key) {
    string result = "";

    // Traverse the ciphertext character by character
    for (int i = 0; i < ciphertext.length(); i++) {
        char c = ciphertext[i];

        // Decrypt uppercase letters
        if (isupper(c)) {
            result += char(int(c - key - 65 + 26) % 26 + 65);
        }
        // Decrypt lowercase letters
        else if (islower(c)) {
            result += char(int(c - key - 97 + 26) % 26 + 97);
        }
        // If it's not an alphabetic character, keep it unchanged
        else {
            result += c;
        }
    }

    return result;
}

// Function to brute-force the Caesar cipher and try all possible keys
void bruteForceCaesar(string ciphertext) {
    // Try all possible keys from 0 to 25
    for (int key = 0; key < 26; key++) {
        string decryptedText = decryptCaesar(ciphertext, key);
        cout << "Key " << key << ": " << decryptedText << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\nCaesar Cipher Application" << endl;
        cout << "1. Encrypt message" << endl;
        cout << "2. Decrypt message with key" << endl;
        cout << "3. Brute-force decryption (no key)" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        cin.ignore();  // To clear the input buffer after reading integer

        if (choice == 1) {
            string plaintext;
            int key;

            cout << "Enter the plaintext: ";
            getline(cin, plaintext);

            cout << "Enter the key (0-25): ";
            cin >> key;

            string encryptedMessage = encryptCaesar(plaintext, key);
            cout << "Encrypted message: " << encryptedMessage << endl;

        } else if (choice == 2) {
            string ciphertext;
            int key;

            cout << "Enter the ciphertext: ";
            getline(cin, ciphertext);

            cout << "Enter the key (0-25): ";
            cin >> key;

            string decryptedMessage = decryptCaesar(ciphertext, key);
            cout << "Decrypted message: " << decryptedMessage << endl;

        } else if (choice == 3) {
            string ciphertext;

            cout << "Enter the ciphertext for brute-force: ";
            getline(cin, ciphertext);

            cout << "Attempting to brute-force decrypt the ciphertext:" << endl;
            bruteForceCaesar(ciphertext);

        } else if (choice == 4) {
            cout << "Exiting the application." << endl;
            break;

        } else {
            cout << "Invalid option, please choose again." << endl;
        }
    }

    return 0;
}
