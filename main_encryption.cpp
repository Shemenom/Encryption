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

    string message0 = "Secret Message";
    demonstrateStreamCipher(message0);

    //Сагайдак Сергей
    std::string message = "Secret Message";
    demonstrateEncryption(message);

    // Шипкова Виктория (блочное шифрование RC6)
    string message1 = "Hello, world!";
    string message2 = "Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!";

    block_cipher_RC6(message1);
    block_cipher_RC6(message2);

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

    // Павел Водопьянов
    vector<uint8_t> key16 = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
                             0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
    
    vector<uint8_t> key24 = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
                             0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,
                             0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    
    vector<uint8_t> key32 = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
                             0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,
                             0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
                             0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00};
    
    cout << "=== ТЕСТИРОВАНИЕ РЕЖИМА ECB С RC6 ===" << endl << endl;
    
    test_ecb_rc6("Hello, World!", key16);
    test_ecb_rc6("Test message for ECB mode", key24);
    test_ecb_rc6("Short", key32);
    test_ecb_rc6("This is a longer message to test ECB mode with RC6 encryption", key16);

    return 0;

}
