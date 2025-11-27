#include <iostream>
#include <string>
#include <vector>
#include "algorithm.h"
using namespace std;

// Инициализация S-блока на основе ключа
void SimpleStreamCipher::initialize(const vector<uint8_t>& key) {
    S.resize(256);
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }

    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key.size()]) % 256;
        swap(S[i], S[j]);
    }
    i = j = 0;
}

// Генерация следующего байта ключевого потока
uint8_t SimpleStreamCipher::generateKeyByte() {
    i = (i + 1) % 256;
    j = (j + S[i]) % 256;
    swap(S[i], S[j]);
    return S[(S[i] + S[j]) % 256];
}

// Конструктор - принимает строковый ключ
SimpleStreamCipher::SimpleStreamCipher(const std::string& key) {
    vector<uint8_t> key_data(key.begin(), key.end());
    initialize(key_data);
}

// Шифрование/дешифрование
vector<char> SimpleStreamCipher::process(const vector<char>& input) {
    vector<char> output;
    output.reserve(input.size());

    for (char input_byte : input) {
        uint8_t key_byte = generateKeyByte();
        output.push_back(static_cast<char>(input_byte ^ key_byte));
    }

    return output;
}

// Функция демонстрации поточного шифрования ARC4
void demonstrateStreamCipher(const std::string& message) {

    string secret_key = "MySecretKey123"; // Строковый ключ вместо числа

    cout << "Исходное сообщение: " << message << endl;
    cout << "Секретный ключ: " << secret_key << endl << endl;

    // Шифрование
    SimpleStreamCipher encryptor(secret_key);
    vector<char> text_vector(message.begin(), message.end());
    vector<char> encrypted = encryptor.process(text_vector);

    cout << "Зашифрованные байты: ";
    for (char c : encrypted) cout << (int)(unsigned char)c << " ";
    cout << endl;

    // Дешифрование (создаем новый объект с тем же ключом)
    SimpleStreamCipher decryptor(secret_key);
    vector<char> decrypted = decryptor.process(encrypted);
    string result(decrypted.begin(), decrypted.end());

    cout << "Расшифрованное сообщение: " << result << endl;

    // Сравнение результатов
    cout << endl << "Результат: " << (message == result ? "УСПЕХ - сообщения идентичны!" : "ОШИБКА - сообщения разные!") << endl;

    // Дополнительные тесты
    cout << endl << "--- ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ---" << endl;

    // Тест с разными ключами
    string wrong_key = "WrongKey";
    SimpleStreamCipher wrong_decryptor(wrong_key);
    vector<char> wrong_decrypted = wrong_decryptor.process(encrypted);
    string wrong_result(wrong_decrypted.begin(), wrong_decrypted.end());

    cout << "Попытка дешифрования неправильным ключом: " << endl;
    cout << "Результат: \"" << wrong_result << "\"" << endl;
    cout << "Ожидалось: \"" << message << "\"" << endl;
    cout << "Совпадение: " << (message == wrong_result ? "ДА (ОШИБКА БЕЗОПАСНОСТИ!)" : "НЕТ (КОРРЕКТНО)") << endl;

    // Тест пустого сообщения
    string empty_message = "";
    SimpleStreamCipher empty_encryptor(secret_key);
    vector<char> empty_encrypted = empty_encryptor.process(vector<char>(empty_message.begin(), empty_message.end()));
    SimpleStreamCipher empty_decryptor(secret_key);
    vector<char> empty_decrypted = empty_decryptor.process(empty_encrypted);
    string empty_result(empty_decrypted.begin(), empty_decrypted.end());

    cout << endl << "Тест пустого сообщения: " << (empty_message == empty_result ? "УСПЕХ" : "ОШИБКА") << endl;
}



