#include "rsa.h"
#include <iostream>
#include <random>
#include <string>

using namespace std;

// Check if number is prime
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

// Greatest common divisor
long long RSA::gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Modular exponentiation
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

// Modular inverse
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

// Generate prime number (simplified version)
long long RSA::generatePrime() {
    // Use fixed prime numbers for stability
    long long primes[] = { 101, 103, 107, 109, 113, 127, 131, 137, 139, 149 };
    static int index = 0;
    return primes[index++ % 10];
}

// Generate key pair
pair<pair<long long, long long>, pair<long long, long long>> RSA::generateKeys() {
    // Choose two distinct prime numbers
    long long p = generatePrime();
    long long q;
    do {
        q = generatePrime();
    } while (q == p);

    // Calculate modulus
    long long n = p * q;

    // Calculate Euler's totient function
    long long phi = (p - 1) * (q - 1);

    // Choose public exponent
    long long e = 65537;

    // Ensure e and phi are coprime
    while (gcd(e, phi) != 1) {
        e++;
    }

    // Calculate private exponent
    long long d = modInverse(e, phi);

    // Return key pairs
    return make_pair(
        make_pair(e, n),  // Public key
        make_pair(d, n)   // Private key
    );
}

// Encrypt number
long long RSA::encrypt(long long message, const pair<long long, long long>& publicKey) {
    long long e = publicKey.first;
    long long n = publicKey.second;
    return modPow(message, e, n);
}

// Decrypt number
long long RSA::decrypt(long long encrypted, const pair<long long, long long>& privateKey) {
    long long d = privateKey.first;
    long long n = privateKey.second;
    return modPow(encrypted, d, n);
}

// Encrypt string
string RSA::encrypt(const string& message, const pair<long long, long long>& publicKey) {
    string encrypted;

    for (char c : message) {
        long long encryptedChar = encrypt(static_cast<long long>(c), publicKey);
        encrypted += to_string(encryptedChar) + " ";
    }

    return encrypted;
}

// Decrypt string with verification
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

    // Convergence check with original string
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