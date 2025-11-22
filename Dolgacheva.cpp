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
void printVector(const vector<char>& vec, const string& name) {
    cout << name << " (как строка): ";
    for (char c : vec) {
        if (c >= 32 && c <= 126) {
            cout << c;
        }
        else {
            cout << '?';
        }
    }
    cout << endl;

    cout << name << " (как байты): ";
    for (unsigned char c : vec) {
        cout << static_cast<int>(c) << " ";
    }
    cout << endl << endl;
}

// Функции тестирования поточного шифрования
void demonstrate_stream_cipher() {
    unsigned long long secret_key = 123456789;

    string plaintext = "Hello, Stream Cipher!";
    vector<char> plaintext_vector(plaintext.begin(), plaintext.end());

    cout << "--- Демонстрация поточного шифрования ---\n" << endl;
    printVector(plaintext_vector, "Исходный текст");

    // ШИФРОВАНИЕ
    SimpleStreamCipher encryptor(secret_key);
    vector<char> ciphertext_vector = encryptor.process(plaintext_vector);
    printVector(ciphertext_vector, "Шифртекст     ");

    // РАСШИФРОВКА
    SimpleStreamCipher decryptor(secret_key);
    vector<char> decrypted_vector = decryptor.process(ciphertext_vector);
    printVector(decrypted_vector, "Расшифрованный");

    // Проверка
    if (equal(plaintext_vector.begin(), plaintext_vector.end(), decrypted_vector.begin())) {
        cout << "УСПЕХ: Расшифрованный текст совпадает с исходным!" << endl;
    }
    else {
        cout << "ОШИБКА: Тексты не совпали!" << endl;
    }
}

void test_stream_performance() {
    cout << "\n=== ТЕСТ ПРОИЗВОДИТЕЛЬНОСТИ ===" << endl;

    unsigned long long secret_key = 987654321;
    string long_text = "This is a longer text for performance testing of stream cipher algorithm.";
    vector<char> long_vector(long_text.begin(), long_text.end());

    SimpleStreamCipher cipher(secret_key);

    vector<char> encrypted = cipher.process(long_vector);

    SimpleStreamCipher decipher(secret_key);
    vector<char> decrypted = decipher.process(encrypted);

    if (equal(long_vector.begin(), long_vector.end(), decrypted.begin())) {
        cout << "УСПЕХ: Длинный текст успешно зашифрован и расшифрован!" << endl;
        cout << "Размер данных: " << long_text.size() << " байт" << endl;
    }
    else {
        cout << "ОШИБКА: Проблема с шифрованием длинного текста!" << endl;
    }
}