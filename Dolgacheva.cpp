#include <iostream>
#include <string>
#include <vector>
using namespace std;

// класс (генератор ключевого потока)
class SimpleStreamCipher {
private:
    unsigned long long current_state; // текущее состояние генератора
    unsigned long long a, c, m;  // параметры ГПСЧ: multiplier, increment, modulus

    // Функция генерации следующего псевдослучайного байта
    char generateKeyByte() {
        current_state = (a * current_state + c) % m;
        return static_cast<char>(current_state & 0xFF); // Берем младший байт
    }

public:
    // Конструктор. seed - это наш секретный ключ.
    SimpleStreamCipher(unsigned long long seed) {
        // Стандартные параметры из Numerical Recipes (не для криптографии!)
        a = 1664525;
        c = 1013904223;
        m = 4294967296; // 2^32
        current_state = seed; // Инициализируем генератор ключом
    }

    // Функция шифрования И расшифровки (благодаря XOR)
    vector<char> process(const vector<char>& input) {
        vector<char> output;
        output.reserve(input.size());

        for (char input_byte : input) {
            // Генерируем байт ключевого потока
            char key_byte = generateKeyByte();
            // Применяем XOR и добавляем результат в выходной вектор
            output.push_back(input_byte ^ key_byte);
        }

        return output;
    }
};

// Вспомогательная функция для вывода вектора в читаемом виде
void printVector(const vector<char>& vec, const string& name) {
    cout << name << " (как строка): ";
    for (char c : vec) {
        // Печатаем только печатные символы, иначе заменяем на '?'
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

// Функция для демонстрации работы поточного шифрования (аналог test_small_numbers)
void demonstrate_stream_cipher() {
    // Секретный ключ (должен быть одинаковым у отправителя и получателя)
    unsigned long long secret_key = 123456789;

    // Исходное сообщение
    string plaintext = "Hello, Stream Cipher!";
    vector<char> plaintext_vector(plaintext.begin(), plaintext.end());

    cout << "--- Демонстрация поточного шифрования ---\n" << endl;
    printVector(plaintext_vector, "Исходный текст");

    // ШИФРОВАНИЕ
    SimpleStreamCipher encryptor(secret_key);
    vector<char> ciphertext_vector = encryptor.process(plaintext_vector);
    printVector(ciphertext_vector, "Шифртекст     ");

    // РАСШИФРОВКА
    // Для расшифровки мы создаем НОВЫЙ объект с тем же ключом.
    // Его внутреннее состояние начнется с того же seed, и он сгенерирует
    // тот же самый ключевой поток.
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

// Дополнительная тестовая функция для больших данных
void test_stream_performance() {
    cout << "\n=== ТЕСТ ПРОИЗВОДИТЕЛЬНОСТИ ===" << endl;

    unsigned long long secret_key = 987654321;
    string long_text = "This is a longer text for performance testing of stream cipher algorithm.";
    vector<char> long_vector(long_text.begin(), long_text.end());

    SimpleStreamCipher cipher(secret_key);

    // Шифрование
    vector<char> encrypted = cipher.process(long_vector);

    // Дешифрование
    SimpleStreamCipher decipher(secret_key);
    vector<char> decrypted = decipher.process(encrypted);

    // Проверка
    if (equal(long_vector.begin(), long_vector.end(), decrypted.begin())) {
        cout << "УСПЕХ: Длинный текст успешно зашифрован и расшифрован!" << endl;
        cout << "Размер данных: " << long_text.size() << " байт" << endl;
    }
    else {
        cout << "ОШИБКА: Проблема с шифрованием длинного текста!" << endl;
    }
}