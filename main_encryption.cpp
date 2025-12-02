#include <iostream>
#include <chrono>
#include <functional>
#include "algorithm.h"

using namespace std::chrono;
using namespace std;

// это не трогать !!!
template<typename Func, typename... Args>
auto Time(Func&& func, Args&&... args) {
    auto start = chrono::high_resolution_clock::now();
    
    std::invoke(forward<Func>(func), forward<Args>(args)...);
    
    auto end = high_resolution_clock::now();
    return chrono::duration_cast< microseconds>(end - start);
}

int main() {
    cout << "=== ТЕСТИРОВАНИЕ СИСТЕМЫ ELGAMAL ===" << endl << endl;

    vector<long long> small_numbers = { 1, 42, 100, 255, 512, 999, 1024, 2048 };
    test_small_numbers(small_numbers);

    vector<long long> huge_numbers = { 1000000000, 2500000000 };
    test_huge_numbers(huge_numbers);

    cout << "=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===" << endl;

    /// Александра Долгачева - тестирование поточного шифрования ARC4
    cout << "\n=== ТЕСТИРОВАНИЕ ПОТОЧНОГО ШИФРОВАНИЯ (ARC4) ===" << endl;

    std::string message = "Secret Message";
    demonstrateStreamCipher(message);

    cout << "=== ТЕСТИРОВАНИЕ ПОТОЧНОГО ШИФРОВАНИЯ ЗАВЕРШЕНО ===" << endl;

    //Сагайдак Сергей
    std::string message = "Secret Message";
    demonstrateEncryption(message);

    // Шипкова Виктория (блочное шифрование RC6)
    string message1 = "Hello, world!";
    string message2 = "Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!";

    block_cipher_RС6(message1);
    block_cipher_RС6(message2);

    // Бардин Глеб
    processRSA("HELLO WORLD");
    processRSA("SECRET MESSAGE");
    processRSA("TEST 123");

    // Бурханов Тахир
    string a(1000, '0');
    string b(1000000, '0');
    test_encryption("Hello, World!", "mysecretkey");
    cout << endl;
    test_encryption(a, "mysecretkey");
    cout << endl;
    test_encryption(b, "mysecretkey");

    return 0;

}
