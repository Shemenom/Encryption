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

// Функция демонстрации поточного шифрования 
void demonstrateStreamCipher(const std::string& message) {
    cout << "=== ДЕМОНСТРАЦИЯ ПОТОЧНОГО ШИФРОВАНИЯ ===" << endl << endl;

    unsigned long long secret_key = 123456789;

    cout << "Исходное сообщение: " << message << endl;
    cout << "Секретный ключ: " << secret_key << endl << endl;

    // Шифрование
    SimpleStreamCipher encryptor(secret_key);
    vector<char> text_vector(message.begin(), message.end());
    vector<char> encrypted = encryptor.process(text_vector);

    cout << "Зашифрованные байты: ";
    for (char c : encrypted) cout << (int)c << " ";
    cout << endl;

    // Дешифрование
    SimpleStreamCipher decryptor(secret_key);
    vector<char> decrypted = decryptor.process(encrypted);
    string result(decrypted.begin(), decrypted.end());

    cout << "Расшифрованное сообщение: " << result << endl;

    // Сравнение результатов
    cout << endl << "Результат: " << (message == result ? "УСПЕХ - сообщения идентичны!" : "ОШИБКА - сообщения разные!") << endl;
}




