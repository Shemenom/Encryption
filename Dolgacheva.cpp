#include <iostream>
#include <string>
#include <vector>

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

