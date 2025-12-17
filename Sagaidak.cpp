#include "algorithm.h"
#include <iostream>
#include <cstdio>

using namespace std;

// Конструктор - создает пару ключей
SimpleECC::SimpleECC(int secret) {
    private_key = secret;
    // Вычисляем публичный ключ: только x-координата
    public_key = (private_key * base_x) % prime;
}

// Вычисление общего секретного ключа с другим пользователем
int SimpleECC::getSharedSecret(int other_public_key) {
    // Общий секрет = наш_приватный * их_публичный
    return (private_key * other_public_key) % prime;
}

// Геттер приватного ключа
int SimpleECC::getPrivateKey() {
    return private_key;
}

// Геттер публичного ключа
int SimpleECC::getPublicKey() {
    return public_key;
}

// Функция шифрования/дешифрования методом XOR
std::string xorEncrypt(std::string text, int key) {
    std::string result = "";
    for (char c : text) {
        result += c ^ (key % 256);  // Используем весь диапазон char
    }
    return result;
}

// Функция демонстрации шифрования
void demonstrateEncryption(const std::string& message) {
    // Создаем двух пользователей
    SimpleECC user1(7);  // Секретный ключ 7
    SimpleECC user2(13); // Секретный ключ 13

    // Вычисляем общие секреты
    int secret1 = user1.getSharedSecret(user2.getPublicKey());
    int secret2 = user2.getSharedSecret(user1.getPublicKey());

    // Шифрование и дешифрование
    if (message.size() < 40) {
        cout << "Исходное сообщение: " << message << endl;
    }
    else {
        cout << "Исходное сообщение: ..." << endl;
    }

    string encrypted = xorEncrypt(message, secret1);
    cout << "Зашифрованное сообщение (hex): ";
    if (encrypted.size() < 40) {
        for (char c : encrypted) {
            printf("%02x ", (unsigned char)c);
        }
    }
    else {
        cout << "...";
    }
    cout << endl;

    string decrypted = xorEncrypt(encrypted, secret2);

    if (decrypted.size() < 40) {
        cout << "Расшифрованное сообщение: " << decrypted << endl;
    }
    else {
        cout << "Расшифрованное сообщение: ..." << endl;
    }

    // Проверка корректности
    cout << endl << "Результат: " << (message == decrypted ? "Успех - сообщение восстановлено!" : "Ошибка - сообщение не совпадает!") << endl;
}