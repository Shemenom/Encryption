#include <iostream>
#include <string>
#include <vector>
#include "algorithm.h"
using namespace std;

// Инициализация S-блока на основе ключа
void SimpleStreamCipher::initialize(const vector<uint8_t>& key) {  // ссылка на массив байтов ключа
    S.resize(256); //устанавливает размер массива 256 элементов
    for (int i = 0; i < 256; i++) {
        S[i] = i;  //присваиваем каждому элементу его индекс
    }

    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key.size()]) % 256;
        swap(S[i], S[j]);
    }
}

// Генерация следующего байта ключевого потока
uint8_t SimpleStreamCipher::generateKeyByte() {  // возвращаемый тип: беззнаковое 8-битное число (0-255)
    i = (i + 1) % 256;
    j = (j + S[i]) % 256;
    swap(S[i], S[j]);
    return S[(S[i] + S[j]) % 256];
}

// Конструктор - принимает строковый ключ
SimpleStreamCipher::SimpleStreamCipher(const string& key) {
    vector<uint8_t> key_data(key.begin(), key.end());  // преобразовывает ключ в байты
    initialize(key_data);
}

// Шифрование/дешифрование
vector<char> SimpleStreamCipher::process(const vector<char>& input) {
    vector<char> output; // Создание выходного массива
    output.reserve(input.size());  // выделяем память на количество элементов в массиве

    for (char input_byte : input) {  // цикл по входным данным
        uint8_t key_byte = generateKeyByte(); // сохраняет в переменную key_byte след байт ключевого потока
        output.push_back(static_cast<char>(input_byte ^ key_byte));  // ^ побитовый оператор XOR
    }

    return output;
}

// Функция демонстрации поточного шифрования ARC4
void demonstrateStreamCipher(const std::string& message0) {

    string secret_key = "MySecretKey123"; // Строковый ключ вместо числа

    cout << "Исходное сообщение: " << message0 << endl;
    cout << "Секретный ключ: " << secret_key << endl << endl;

    // Шифрование
    SimpleStreamCipher encryptor(secret_key);
    vector<char> text_vector(message0.begin(), message0.end());
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
    cout << endl << "Результат: " << (message0 == result ? "УСПЕХ - сообщения идентичны!" : "ОШИБКА - сообщения разные!") << endl;
}



