#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <string>
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

#endif