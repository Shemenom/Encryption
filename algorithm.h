#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cmath>
#include <string>
#include <algorithm>
#include <tuple>

#ifndef ELGAMAL_UNIVERSAL_H
#define ELGAMAL_UNIVERSAL_H

using namespace std;

class ElGamalUniversal {
private:
    long long p, g, x, y;  // Параметры системы: p - простое число, g - генератор, x - закрытый ключ, y - открытый ключ
    std::random_device rd;       // Аппаратный генератор случайных чисел
    std::mt19937 gen;            // Генератор псевдослучайных чисел (вихрь Мерсенна)

    // Быстрое возведение в степень по модулю
    long long mod_pow(long long base, long long exponent, long long mod);

    // Проверка числа на простоту методом Миллера-Рабина
    bool is_prime(long long n, int iterations = 15);

    // Генерация простого числа в заданном диапазоне
    long long generate_prime(long long min_val, long long max_val);

    // Поиск первообразного корня по модулю p
    long long find_primitive_root(long long p);

    // Вычисление наибольшего общего делителя (НОД)
    long long gcd(long long a, long long b);
public:
    // Конструктор - инициализация криптосистемы
    ElGamalUniversal(std::string size = "medium");

    // Шифрование числа
    std::pair<long long, long long> encrypt_number(long long number);

    // Расшифрование числа
    long long decrypt_number(std::pair<long long, long long> ciphertext);

    // Вывод информации о системе
    void print_info();

    // Проверка корректности работы системы
    bool is_valid();
};
