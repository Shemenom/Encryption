#include "aes.h"
#include <iostream>

void SimpleAES::prepare_key() {
    if (key.size() < 16) {
        while (key.size() < 16) {
            key.push_back(0x00);
        }
    }
    else if (key.size() > 16) {
        key.resize(16);
    }
}

void SimpleAES::xor_with_key(vector<unsigned char>& data) {
    for (size_t i = 0; i < data.size(); i++) {
        data[i] ^= key[i % key.size()];
    }
}

void SimpleAES::substitute_bytes(vector<unsigned char>& data) {
    for (size_t i = 0; i < data.size(); i++) {
        data[i] = (data[i] + 123) & 0xFF;
    }
}

void SimpleAES::shift_data(vector<unsigned char>& data) {
    if (data.empty()) return;

    unsigned char first = data[0];
    for (size_t i = 0; i < data.size() - 1; i++) {
        data[i] = data[i + 1];
    }
    data[data.size() - 1] = first;
}

SimpleAES::SimpleAES(const string& key_str) {
    for (char c : key_str) {
        key.push_back(static_cast<unsigned char>(c));
    }
    prepare_key();
}

vector<unsigned char> SimpleAES::encrypt(const vector<unsigned char>& input) {
    vector<unsigned char> result = input;

    while (result.size() % 16 != 0) {
        result.push_back(0x00);
    }

    for (int round = 0; round < 3; round++) {
        substitute_bytes(result);
        shift_data(result);
        xor_with_key(result);
    }

    return result;
}

vector<unsigned char> SimpleAES::decrypt(const vector<unsigned char>& input) {
    vector<unsigned char> result = input;

    for (int round = 0; round < 3; round++) {
        xor_with_key(result);

        if (!result.empty()) {
            unsigned char last = result[result.size() - 1];
            for (size_t i = result.size() - 1; i > 0; i--) {
                result[i] = result[i - 1];
            }
            result[0] = last;
        }

        for (size_t i = 0; i < result.size(); i++) {
            result[i] = (result[i] - 123) & 0xFF;
        }
    }

    return result;
}

string aes_encrypt(const string& text, const string& key) {
    SimpleAES aes(key);

    vector<unsigned char> input_bytes;
    for (char c : text) {
        input_bytes.push_back(static_cast<unsigned char>(c));
    }

    vector<unsigned char> encrypted_bytes = aes.encrypt(input_bytes);

    string result;
    for (unsigned char byte : encrypted_bytes) {
        result += static_cast<char>(byte);
    }

    return result;
}

string aes_decrypt(const string& text, const string& key) {
    SimpleAES aes(key);

    vector<unsigned char> input_bytes;
    for (char c : text) {
        input_bytes.push_back(static_cast<unsigned char>(c));
    }

    vector<unsigned char> decrypted_bytes = aes.decrypt(input_bytes);

    // Удаляем нулевые байты в конце
    while (!decrypted_bytes.empty() && decrypted_bytes.back() == 0x00) {
        decrypted_bytes.pop_back();
    }

    string result;
    for (unsigned char byte : decrypted_bytes) {
        result += static_cast<char>(byte);
    }

    return result;
}

void test_encryption(const string& text, const string& key) {
    string encrypted = aes_encrypt(text, key);
    string decrypted = aes_decrypt(encrypted, key);

    if (text.size() < 40) {
        cout << "Original text: " << text << endl;
    } else {
        cout << "Original text: ... " << endl;
    }

    cout << "Encrypted text (hex): ";
    if (encrypted.size() < 40) {
        for (char c : encrypted) {
            cout << hex << (int)(unsigned char)c << " ";
        }
    } else {
        cout << "...";
    }
    cout << dec << endl;

    if (decrypted.size() < 40) {
        cout << "Decrypted text: " << decrypted << endl;
    } else {
        cout << "Decrypted text: ... "  << endl;
    }   

    if (text == decrypted) {
        cout << "Encryption/decryption successful!" << endl;
    }
    else {
        cout << "Encryption error!" << endl;
    }
}
