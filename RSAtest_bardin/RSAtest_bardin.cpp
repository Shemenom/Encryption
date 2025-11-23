#include <iostream>
#include "rsa.h"

using namespace std;

int main() {
    cout << "=== RSA ALGORITHM TEST ===" << endl;
    cout << "Generating keys..." << endl;

    // 1. Generate keys
    auto keys = RSA::generateKeys();
    auto publicKey = keys.first;
    auto privateKey = keys.second;

    cout << "✓ Keys generated!" << endl;
    cout << "Public key (e, n): (" << publicKey.first << ", " << publicKey.second << ")" << endl;
    cout << "Private key (d, n): (" << privateKey.first << ", " << privateKey.second << ")" << endl;
    cout << endl;

    // 2. Test message
    string originalMessage = "HELLO RSA";
    cout << "Original message: " << originalMessage << endl;

    // 3. Encryption
    cout << "Encrypting..." << endl;
    string encrypted = RSA::encrypt(originalMessage, publicKey);
    cout << "Encrypted message: " << encrypted << endl;
    cout << endl;

    // 4. Decryption with check
    cout << "Decrypting with check..." << endl;
    string decrypted = RSA::decrypt(encrypted, privateKey, originalMessage);
    cout << "Decrypted message: " << decrypted << endl;
    cout << endl;

    // 5. Additional test - number encryption
    cout << "=== ADDITIONAL TEST ===" << endl;
    long long testNumber = 123;
    cout << "Test number: " << testNumber << endl;

    long long encryptedNumber = RSA::encrypt(testNumber, publicKey);
    cout << "Encrypted number: " << encryptedNumber << endl;

    long long decryptedNumber = RSA::decrypt(encryptedNumber, privateKey);
    cout << "Decrypted number: " << decryptedNumber << endl;

    cout << "=== TEST COMPLETED ===" << endl;

    // Pause to see the result
    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}