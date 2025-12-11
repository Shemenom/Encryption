#include <iostream>
#include <string>
#include <vector>
#include "algorithm.h"
using namespace std;

// Инициализация S-блока по алгоритму KSA
void SimpleStreamCipher::initialize(const vector<uint8_t>& key) { // KSA (Key Scheduling Algorithm)
    S.resize(256); // Инициализируем массив размером 256 элементов
    for (int k = 0; k < 256; k++) {
        S[k] = k; // Заполняем массив значениями от 0 до 255
    }

    int j = 0;
    for (int k = 0; k < 256; k++) {
        j = (j + S[k] + key[k % key.size()]) % 256;
        swap(S[k], S[j]);
    }
}

// Генерация псевдослучайного байта ключевого потока
uint8_t SimpleStreamCipher::generateKeyByte() {  // Генерация байта: псевдослучайный 8-битный байт (0-255)
    i = (i + 1) % 256;
    j = (j + S[i]) % 256;
    swap(S[i], S[j]);
    return S[(S[i] + S[j]) % 256];
}

// Конструктор - инициализация с ключом
SimpleStreamCipher::SimpleStreamCipher(const string& key) : i(0), j(0) {
    vector<uint8_t> key_data(key.begin(), key.end());  // Преобразуем ключ в байты
    initialize(key_data);
}

// Шифрование/дешифрование
vector<char> SimpleStreamCipher::process(const vector<char>& input) {
    // Важно: сбрасываем индексы перед каждой обработкой!
    i = 0;
    j = 0;
    vector<char> output; // Вектор для результата
    output.reserve(input.size());  // Резервируем память для повышения эффективности

    for (char input_byte : input) {  // Цикл по входным данным
        uint8_t key_byte = generateKeyByte(); // Генерируем байт ключевого потока
        output.push_back(static_cast<char>(input_byte ^ key_byte));  // ^ выполняет операцию XOR
    }

    return output;
}

// Функция для демонстрации работы поточного шифра ARC4
void demonstrateStreamCipher(const std::string& message0) {
    string secret_key = "MySecretKey123"; // Секретный ключ для шифрования

    cout << "Исходное сообщение: " << message0 << endl;
    cout << "Используемый ключ: " << secret_key << endl << endl;

    // Шифрование
    SimpleStreamCipher encryptor(secret_key);
    vector<char> text_vector(message0.begin(), message0.end());
    vector<char> encrypted = encryptor.process(text_vector);

    cout << "Зашифрованные байты: ";
    for (char c : encrypted) {
        cout << (int)(unsigned char)c << " ";
    }
    cout << endl;

    // Дешифрование (используем тот же алгоритм с тем же ключом)
    SimpleStreamCipher decryptor(secret_key);
    vector<char> decrypted = decryptor.process(encrypted);
    string result(decrypted.begin(), decrypted.end());

    cout << "Расшифрованное сообщение: " << result << endl;

    // Для наглядности - выводим байты расшифрованного текста
    cout << "Расшифрованные байты как числа: ";
    for (char c : decrypted) {
        cout << (int)(unsigned char)c << " ";
    }
    cout << endl;

    // Проверка корректности
    bool success = (message0 == result);
    cout << endl << "Результат: " << (success ? "Успех - сообщение восстановлено!" : "Ошибка - сообщение не совпадает!") << endl;
}