#include "algorithm.h"
#include <iostream>
#include <random>
#include <string>

using namespace std;

// ========== РЕАЛИЗАЦИЯ RSA МАТЕМАТИКИ ==========

bool RSA::isPrime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

long long RSA::gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long RSA::modPow(long long base, long long exponent, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        exponent = exponent >> 1;
        base = (base * base) % mod;
    }
    return result;
}

long long RSA::modInverse(long long a, long long m) {
    long long m0 = m;
    long long y = 0, x = 1;

    if (m == 1) return 0;

    while (a > 1) {
        long long q = a / m;
        long long t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0) x += m0;

    return x;
}

long long RSA::generatePrime() {
    long long primes[] = { 101, 103, 107, 109, 113, 127, 131, 137, 139, 149 };
    static int index = 0;
    return primes[index++ % 10];
}

pair<pair<long long, long long>, pair<long long, long long>> RSA::generateKeys() {
    long long p = generatePrime();
    long long q;
    do {
        q = generatePrime();
    } while (q == p);

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = 65537;

    while (gcd(e, phi) != 1) {
        e++;
    }

    long long d = modInverse(e, phi);

    return make_pair(
        make_pair(e, n),
        make_pair(d, n)
    );
}

long long RSA::encrypt(long long message, const pair<long long, long long>& publicKey) {
    long long e = publicKey.first;
    long long n = publicKey.second;
    return modPow(message, e, n);
}

long long RSA::decrypt(long long encrypted, const pair<long long, long long>& privateKey) {
    long long d = privateKey.first;
    long long n = privateKey.second;
    return modPow(encrypted, d, n);
}

string RSA::encrypt(const string& message, const pair<long long, long long>& publicKey) {
    string encrypted;

    for (char c : message) {
        long long encryptedChar = encrypt(static_cast<long long>(c), publicKey);
        encrypted += to_string(encryptedChar) + " ";
    }

    return encrypted;
}

string RSA::decrypt(const string& encrypted, const pair<long long, long long>& privateKey, const string& original) {
    string decrypted;
    string encryptedCharStr;

    for (char c : encrypted) {
        if (c == ' ') {
            if (!encryptedCharStr.empty()) {
                long long encryptedChar = stoll(encryptedCharStr);
                long long decryptedChar = decrypt(encryptedChar, privateKey);
                decrypted += static_cast<char>(decryptedChar);
                encryptedCharStr.clear();
            }
        }
        else {
            encryptedCharStr += c;
        }
    }

    if (!original.empty()) {
        bool matches = (decrypted == original);
        cout << "Convergence check: " << (matches ? "SUCCESS" : "ERROR") << endl;
        if (!matches) {
            cout << "Expected: " << original << endl;
            cout << "Received: " << decrypted << endl;
        }
    }

    return decrypted;
}

// ========== РЕАЛИЗАЦИЯ ФУНКЦИЙ ОБРАБОТКИ ==========

void processRSA(const string& message,  
                const pair<long long, long long>& publicKey, 
                const pair<long long, long long>& privateKey) { 
     
    cout << "\n=== RSA PROCESSING ===" << endl; 
     
    // Показываем только начало исходного сообщения 
    cout << "Исходное сообщение: "; 
    if (message.length() > 40) { 
        cout << message.substr(0, 40) << "... (" << message.length() << " символов)" << endl; 
    } else { 
        cout << message << endl; 
    } 
     
    auto keys = (publicKey.first == 0) ? RSA::generateKeys() : make_pair(publicKey, privateKey); 
    auto pubKey = keys.first; 
    auto privKey = keys.second; 
     
    cout << "Публичный ключ: (" << pubKey.first << ", " << pubKey.second << ")" << endl; 
     
    string encrypted = RSA::encrypt(message, pubKey); 
    string decrypted = RSA::decrypt(encrypted, privKey, message); 
     
    // Показываем только начало зашифрованных данных 
    cout << "Зашифрованные данные: "; 
    if (encrypted.length() > 40) { 
        cout << encrypted.substr(0, 40) << "... (" << encrypted.length() << " символов)" << endl; 
    } else { 
        cout << encrypted << endl; 
    } 
     
    // Показываем только начало расшифрованных данных 
    cout << "Расшифрованное сообщение: "; 
    if (decrypted.length() > 40) { 
        cout << decrypted.substr(0, 40) << "... (" << decrypted.length() << " символов)" << endl; 
    } else { 
        cout << decrypted << endl; 
    } 
     
    // Проверка 
    cout << "Результат: " << (message == decrypted ? "УСПЕХ" : "ОШИБКА") << endl; 
    cout << "=== ЗАВЕРШЕНО ===" << endl << endl; 
}

// Перегрузка для автоматической генерации ключей
void processRSA(const string& message) {
    processRSA(message, {0, 0}, {0, 0});
}

