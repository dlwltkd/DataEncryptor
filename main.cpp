#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <limits>

const char XOR_SECRET = 42;

std::string encrypt(const std::string& text, const std::string& key);
std::string deEncrypt(const std::string& encrypted, const std::string& key);
std::string generateKey(int length);

int main() {
    std::cout << "Welcome to data encryptor.\nTo encrypt: Press 1.\nTo decrypt: Press 2.\n";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer

    while (choice == 1) {
        std::cout << "Enter name of file to contain data encryption (include .txt):\n";
        std::string fileName;
        std::getline(std::cin, fileName);
        std::ofstream outFile(fileName);

        if (!outFile.is_open()) {
            std::cerr << "Error: Unable to open file '" << fileName << "'.\n";
            continue;
        }

        std::cout << "Enter data to be encrypted:\n";
        std::string unEncryptedData;
        std::getline(std::cin, unEncryptedData);

        std::string key = generateKey((std::rand() % 29) + 10);
        std::cout << "This is your key (do not share): \n" << key << std::endl;

        std::string encryptedData = encrypt(unEncryptedData, key);
        outFile << encryptedData;
        outFile.close();

        std::cout << "Data encrypted and saved to '" << fileName << "'.\n";
        std::cout << "Would you like to decrypt (press 2) or encrypt another (press 1)?\n";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
    }

    while (choice == 2) {
        std::cout << "Welcome to decrytor.\nEnter encrypted text:\n";
        std::string text;
        std::cin >> text;
        std::cout << "Enter key:\n";
        std::string key;
        std::cin >> key;

        std::string decryptedData = deEncrypt(text, key);
        std::cout << "Your decrypted message is: " << decryptedData << "\n";

        std::cout << "To encrypt again (press 1) or decrypt more (press 2): ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer
    }

    return 0;
}

// Encryption and decryption functions are unchanged.



std::string encrypt(const std::string& text, const std::string& key){
    std::string encrypted = text;
    //shift each character by the ASCII value of key character
    for (size_t i = 0; i < encrypted.size(); ++i ){
        encrypted[i] = encrypted[i] + key[i % key.size()];
    }
    //XOR each char with value
    char secret = XOR_SECRET; // choose any value 
    for (char& c  :encrypted){
        c ^= secret;
    }

    //reverse string 

    std::reverse(encrypted.begin(), encrypted.end());

    return encrypted;



}
std::string deEncrypt(const std::string& encrypted, const std::string& key){

    std::string decrypted = encrypted;
    //reverse
    std::reverse(decrypted.begin(),decrypted.end());
    //xor each value with secret value
    char secret = XOR_SECRET;
    for (char& c : decrypted) {
        c ^= secret;
    }

    //shift each character back by the ASCII value of the key character
    for (size_t i = 0; i < decrypted.size(); ++i){
        decrypted[i] = decrypted[i] - key[i % key.size()];
    }
    return decrypted;

    



}

std::string generateKey(int length) {
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    const int charactersCount = characters.size();
    std::string key = "";

    
    for (int i = 0; i < length; ++i) {
        key += characters[std::rand() % charactersCount];
    }
    return key;
}
