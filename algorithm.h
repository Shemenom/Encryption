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


// Александра Долгачева (поточное шифрование)
class SimpleStreamCipher {
private:
    unsigned long long current_state;
    unsigned long long a, c, m;

    char generateKeyByte();

public:
    SimpleStreamCipher(unsigned long long seed);
    vector<char> process(const vector<char>& input);
};

// Функции тестирования поточного шифрования 
void test_stream_small_texts();
void test_stream_large_texts();

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

    void KeyExpansion(const vector<uint8_t>& K); 

    void BytesToBlock(const vector<uint8_t>& bytes, uint32_t block[4]) const;
    void BlockToBytes(const uint32_t block[4], vector<uint8_t>& bytes) const;

    vector<uint8_t> Pad(const vector<uint8_t>& data) const;
    vector<uint8_t> Unpad(const vector<uint8_t>& data) const;
    vector<uint8_t> GenerateIV() const;

    static constexpr int w = 32;        
    static constexpr int u = w / 8;     
    static constexpr uint32_t lgw = 5;

    int r;                    
    vector<uint32_t> S;  

public:
    RC6(const vector<uint8_t>& K, int rounds = 20);

    vector<uint8_t> EncryptBlock(const vector<uint8_t>& plaintext) const;
    vector<uint8_t> DecryptBlock(const vector<uint8_t>& ciphertext) const;

    vector<uint8_t> EncryptCBC(const vector<uint8_t>& plaintext) const;
    vector<uint8_t> DecryptCBC(const vector<uint8_t>& ciphertext) const;
};

void block_cipher_RC6(const string& message);

// Павел Водопьянов 
class ECB {
private:
    void (*encrypt_block)(const vector<uint8_t>&, vector<uint8_t>&, const vector<uint8_t>&);
    void (*decrypt_block)(const vector<uint8_t>&, vector<uint8_t>&, const vector<uint8_t>&);
    int block_size;
    vector<uint8_t> key;

public:
    ECB(void (*enc_func)(const vector<uint8_t>&, vector<uint8_t>&, const vector<uint8_t>&), 
        void (*dec_func)(const vector<uint8_t>&, vector<uint8_t>&, const vector<uint8_t>&),
        const vector<uint8_t>& key_data, int blk_size = 16);
    
    vector<uint8_t> encrypt(const vector<uint8_t>& data);
    vector<uint8_t> decrypt(const vector<uint8_t>& data);
};

// Объявление тестовой функции
void test_ecb_rc6(const string& input_str, const vector<uint8_t>& key);
