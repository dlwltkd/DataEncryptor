#include <iostream> 
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>


std::string encrypt(const std::string& text, const std::string& key);
std::string deEncrypt(const std::string& encrypted, const std::string& key);
std::string generateKey(int length);
const char XOR_SECRET = 42;

int main() {
    
   
    std::string unEncryptedData;
    std::cout << "Welcome to data encryptor.\nTo encrypt: Press 1.\nTo decrypt: press 2:\n";\
    int choice;
    std::cin >> choice;
    std::cout << std::endl;
    while (choice == 1)
    {
    std::cout << "Enter name of file to contain data encryption(include .txt...):\n";
    std::string fileName;
    std::cin >> fileName;
    std::ofstream outFile(fileName);

    std::cout << "Enter Data to be encrypted:\n";
    std::getline(std::cin, unEncryptedData);
    
    std::srand(std::time(nullptr));
    int randKeyLength = (std::rand() % 29) + 10;
    std::string key = generateKey(randKeyLength);
    std::cout << "This is your key(do not share): \n" << key << std::endl;
    
    std::string encryptedData = encrypt(unEncryptedData, key);
    outFile << encryptedData;
    std::cout << "would you like to decrypt (press 2) or geep going (press 1)?";
    std::cin >> choice;
    }
    while (choice == 2) {
    std::cout << "Welcome to decrytor.\nEnter Encrypted text:\n";
    std::string text;
    std::cin >> text;
    std::cout << "Enter key:\n";
    std::string key;
    std::cin >> key;
    std::cout << "Your decrypted message is:";
    std::cout << deEncrypt(text,key);
    std::cout << "Input(1) Output(2): ";
    std::cin >> choice;
    std::cout << std::endl;
        }





    return 0;

}


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
