#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <tuple>

#ifndef ELGAMAL_UNIVERSAL_H
#define ELGAMAL_UNIVERSAL_H

using namespace std;

// Матвей Хлебников 
class ElGamalUniversal {
private:
    long long p, g, x, y;  
    std::random_device rd;
    std::mt19937 gen;

    long long mod_pow(long long base, long long exponent, long long mod);

    bool is_prime(long long n, int iterations = 15);

    long long generate_prime(long long min_val, long long max_val);

    long long find_primitive_root(long long p);

    long long gcd(long long a, long long b);

public:
    ElGamalUniversal(std::string size = "medium");

    std::pair<long long, long long> encrypt_number(long long number);

    long long decrypt_number(std::pair<long long, long long> ciphertext);

    void print_info();

    bool is_valid();
};

void test_small_numbers(const std::vector<long long>& numbers_to_encrypt);

void test_huge_numbers(const std::vector<long long>& numbers_to_encrypt);


// Александра Долгачева (поточное шифрование ARC4)
class SimpleStreamCipher {
private:
    vector<uint8_t> S; // S-блок 256 байт
    int i, j;

    void initialize(const vector<uint8_t>& key);
    uint8_t generateKeyByte();

public:
    SimpleStreamCipher(const string& key);
    vector<char> process(const vector<char>& input);
};

void demonstrateStreamCipher(const string& message);

// Функция шифрования/дешифрования методом XOR
string xorEncrypt(std::string text, int key);

// Функция демонстрации шифрования
void demonstrateEncryption(const string& message);



//Сагайдак Сергей (эднптичексие кривые)
class SimpleECC {
private:
    int prime = 23;        // Простое число для модульной арифметики
    int base_x = 5;        // Базовая точка на кривой (генератор)
    int base_y = 1;
    int private_key;       // Приватный (секретный) ключ
    int public_x;          // Публичный ключ - x координата
    int public_y;          // Публичный ключ - y координата

public:
    // Конструктор - создает пару ключей
    SimpleECC(int secret);

    // Вычисление общего секретного ключа с другим пользователем
    int getSharedSecret(int other_public_x, int other_public_y);

    // Геттеры для доступа к ключам
    int getPrivateKey();
    int getPublicX();
    int getPublicY();
};

// Функция шифрования/дешифрования методом XOR
std::string xorEncrypt(std::string text, int key);

// Функция демонстрации шифрования
void demonstrateEncryption(const std::string& message);


#endif

// Шипкова Виктория (блочное шифрование RC6)
class RC6 {
private:
  
    uint32_t ROTL(uint32_t x, uint32_t n) const;  
    uint32_t ROTR(uint32_t x, uint32_t n) const;  

    void KeyExpansion(const std::vector<uint8_t>& K); 

    void BytesToBlock(const std::vector<uint8_t>& bytes, uint32_t block[4]) const;
    void BlockToBytes(const uint32_t block[4], std::vector<uint8_t>& bytes) const;

    std::vector<uint8_t> Pad(const std::vector<uint8_t>& data) const;
    std::vector<uint8_t> Unpad(const std::vector<uint8_t>& data) const;
    std::vector<uint8_t> GenerateIV() const;

    static constexpr int w = 32;        
    static constexpr int u = w / 8;     
    static constexpr uint32_t lgw = 5;

    int r;                    
    std::vector<uint32_t> S;  

public:
    RC6(const std::vector<uint8_t>& K, int rounds = 20);

    std::vector<uint8_t> EncryptBlock(const std::vector<uint8_t>& plaintext) const;
    std::vector<uint8_t> DecryptBlock(const std::vector<uint8_t>& ciphertext) const;

    std::vector<uint8_t> EncryptCBC(const std::vector<uint8_t>& plaintext) const;
    std::vector<uint8_t> DecryptCBC(const std::vector<uint8_t>& ciphertext) const;
};

void block_cipher_RC6(const std::string& message);

// Бардин Глеб

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

// Функции обработки (добавляем в algorithm.h)
void processRSA(const std::string& message);
void processRSA(const std::string& message, 
                const std::pair<long long, long long>& publicKey,
                const std::pair<long long, long long>& privateKey);

// Бурханов Тахир

class SimpleAES {
private:
    vector<unsigned char> key;
    void prepare_key();
    void xor_with_key(vector<unsigned char>& data);
    void substitute_bytes(vector<unsigned char>& data);
    void shift_data(vector<unsigned char>& data);

public:
    SimpleAES(const string& key_str);
    vector<unsigned char> encrypt(const vector<unsigned char>& input);
    vector<unsigned char> decrypt(const vector<unsigned char>& input);
};

string aes_encrypt(const string& plaintext, const string& key);
string aes_decrypt(const string& ciphertext, const string& key);
void test_encryption(const string& text, const string& key);
