#include <iostream>
#include <string>
#include <vector>
#include "algorithm.h"
using namespace std;

char SimpleStreamCipher::generateKeyByte() {
    current_state = (a * current_state + c) % m;
    return static_cast<char>(current_state & 0xFF);
}

SimpleStreamCipher::SimpleStreamCipher(unsigned long long seed) {
    a = 1664525;
    c = 1013904223;
    m = 4294967296;
    current_state = seed;
}

vector<char> SimpleStreamCipher::process(const vector<char>& input) {
    vector<char> output;
    output.reserve(input.size());

    for (char input_byte : input) {
        char key_byte = generateKeyByte();
        output.push_back(input_byte ^ key_byte);
    }

    return output;
}

// Вспомогательная функция для вывода вектора
void printStreamVector(const vector<char>& vec, const string& name) {
    cout << name << " (строка): ";
    for (char c : vec) {
        if (c >= 32 && c <= 126) {
            cout << c;
        }
        else {
            cout << '?';
        }
    }
    cout << endl;

    cout << name << " (байты): ";
    for (unsigned char c : vec) {
        cout << static_cast<int>(c) << " ";
    }
    cout << endl << endl;
}

// Тест для коротких текстов 
void test_stream_small_texts() {
    cout << "=== ТЕСТ ПОТОЧНОГО ШИФРОВАНИЯ (КОРОТКИЕ ТЕКСТЫ) ===" << endl;

    vector<string> texts_to_encrypt = {
        "Hello",
        "Test",
        "Cipher",
        "Secret",
        "Message"
    };

    unsigned long long secret_key = 123456789;

    for (const string& text : texts_to_encrypt) {
        vector<char> text_vector(text.begin(), text.end());

        // Шифрование
        SimpleStreamCipher encryptor(secret_key);
        vector<char> encrypted = encryptor.process(text_vector);

        // Дешифрование
        SimpleStreamCipher decryptor(secret_key);
        vector<char> decrypted = decryptor.process(encrypted);
        string result(decrypted.begin(), decrypted.end());

        if (text == result) {
            cout << text << " -> УСПЕХ" << endl;
        }
        else {
            cout << "ОШИБКА: " << text << " -> " << result << endl;
        }
    }
    cout << endl;
}

// Тест для длинных текстов 
void test_stream_large_texts() {
    cout << "=== ТЕСТ ПОТОЧНОГО ШИФРОВАНИЯ (ДЛИННЫЕ ТЕКСТЫ) ===" << endl;

    vector<string> large_texts = {
        "This is a longer text for testing stream cipher performance with more data",
        "Another example of substantial text to evaluate encryption efficiency properly"
    };

    unsigned long long secret_key = 987654321;

    for (const string& text : large_texts) {
        vector<char> text_vector(text.begin(), text.end());

        // Шифрование
        SimpleStreamCipher encryptor(secret_key);
        vector<char> encrypted = encryptor.process(text_vector);

        // Дешифрование
        SimpleStreamCipher decryptor(secret_key);
        vector<char> decrypted = decryptor.process(encrypted);
        string result(decrypted.begin(), decrypted.end());

        if (text == result) {
            cout << "Текст длиной " << text.length() << " символов -> УСПЕХ" << endl;
        }
        else {
            cout << "ОШИБКА: текст длиной " << text.length() << " символов" << endl;
        }
    }
    cout << endl;
}