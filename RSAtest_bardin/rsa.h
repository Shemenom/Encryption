#ifndef RSA_H
#define RSA_H

#include <string>
#include <utility>

class RSA {
public:
    // Генерация ключей
    static std::pair<std::pair<long long, long long>, std::pair<long long, long long>> generateKeys();

    // Шифрование строки
    static std::string encrypt(const std::string& message, const std::pair<long long, long long>& publicKey);

    // Дешифрование строки с проверкой
    static std::string decrypt(const std::string& encrypted, const std::pair<long long, long long>& privateKey, const std::string& original = "");

    // Шифрование числа
    static long long encrypt(long long message, const std::pair<long long, long long>& publicKey);

    // Дешифрование числа
    static long long decrypt(long long encrypted, const std::pair<long long, long long>& privateKey);

private:
    // Математические функции для RSA
    static bool isPrime(long long n);
    static long long gcd(long long a, long long b);
    static long long modPow(long long base, long long exponent, long long mod);
    static long long modInverse(long long a, long long m);
    static long long generatePrime();
};

#endif
