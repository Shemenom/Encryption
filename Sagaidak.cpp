#include "algorithm.h"

using namespace std;

// Конструктор - создает пару ключей
SimpleECC::SimpleECC(int secret) {
    private_key = secret;
    // Вычисляем публичный ключ: Public = Private * BasePoint
    public_x = (private_key * base_x) % prime;
    public_y = (private_key * base_y) % prime;
}

// Вычисление общего секретного ключа с другим пользователем
int SimpleECC::getSharedSecret(int other_public_x, int other_public_y) {
    // Общий секрет = наш_приватный * их_публичный
    return (private_key * other_public_x) % prime;
}

// Геттер приватного ключа
int SimpleECC::getPrivateKey() {
    return private_key;
}

// Геттер x-координаты публичного ключа
int SimpleECC::getPublicX() {
    return public_x;
}

// Геттер y-координаты публичного ключа
int SimpleECC::getPublicY() {
    return public_y;
}

// Функция шифрования/дешифрования методом XOR
std::string xorEncrypt(std::string text, int key) {
    std::string result = "";
    for (char c : text) {
        // XOR каждого символа с ключом
        result += c ^ (key % 128);  // %128 чтобы остаться в диапазоне ASCII
    }
    return result;
}

// Функция демонстрации шифрования
void demonstrateEncryption(const std::string& message) {
    // Создаем два пользователя
    SimpleECC user1(7);
    SimpleECC user2(13);

    // Вычисляем общие секреты
    int secret1 = user1.getSharedSecret(user2.getPublicX(), user2.getPublicY());
    int secret2 = user2.getSharedSecret(user1.getPublicX(), user1.getPublicY());

    // Шифрование и дешифрование
    if (message.size() < 40) {
        cout << "Исходное сообщение: " << message << endl;
    }
    else {
        cout << "Исходное сообщение: ..." << endl;
    }

    string encrypted = xorEncrypt(message, secret1);
    cout << "Зашифрованное сообщение: ";
    if (encrypted.size() < 40) {
        for (char c : encrypted) cout << (int)c << " ";
    }
    else {
        cout << " ... ";
    }
    cout << endl;

    string decrypted = xorEncrypt(encrypted, secret2);

    if (encrypted.size() < 40) {
        cout << "Расшифрованное сообщение: " << decrypted << endl;

    }
    else {
        cout << "Расшифрованное сообщение: ... " << endl;
    }

    // Проверка корректности
    cout << endl << "Результат: " << (message == decrypted ? "Успех - сообщение восстановлено!" : "Ошибка - сообщение не совпадает!") << endl;
}