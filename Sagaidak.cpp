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
    cout << "=== ДЕМОНСТРАЦИЯ ШИФРОВАНИЯ ECC ===" << endl << endl;

    // Создаем двух пользователей
    SimpleECC user1(7);
    SimpleECC user2(13);

    // Показываем ключи
    cout << "Ключи пользователя 1:" << endl;
    cout << "Приватный: " << user1.getPrivateKey() << endl;
    cout << "Публичный: (" << user1.getPublicX() << ", " << user1.getPublicY() << ")" << endl << endl;

    cout << "Ключи пользователя 2:" << endl;
    cout << "Приватный: " << user2.getPrivateKey() << endl;
    cout << "Публичный: (" << user2.getPublicX() << ", " << user2.getPublicY() << ")" << endl << endl;

    // Вычисляем общий секрет
    int secret1 = user1.getSharedSecret(user2.getPublicX(), user2.getPublicY());
    int secret2 = user2.getSharedSecret(user1.getPublicX(), user1.getPublicY());

    cout << "Общий секрет пользователя 1: " << secret1 << endl;
    cout << "Общий секрет пользователя 2: " << secret2 << endl;
    cout << "Секреты совпадают: " << (secret1 == secret2 ? "Да" : "Нет") << endl << endl;

    // Шифрование и дешифрование
    cout << "Исходное сообщение: " << message << endl;

    string encrypted = xorEncrypt(message, secret1);
    cout << "Зашифрованное сообщение: ";
    for (char c : encrypted) cout << (int)c << " ";
    cout << endl;

    string decrypted = xorEncrypt(encrypted, secret2);
    cout << "Расшифрованное сообщение: " << decrypted << endl;

    // Сравнение результатов
    cout << endl << "Сравнение: " << (message == decrypted ? "УСПЕХ - сообщения идентичны!" : "ОШИБКА - сообщения разные!") << endl;
}