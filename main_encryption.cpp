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

    //// Долгачева Александра
    cout << "\n=== ТЕСТИРОВАНИЕ ПОТОЧНОГО ШИФРОВАНИЯ ===" << endl;
    test_stream_small_texts();
    test_stream_large_texts();
    cout << "=== ТЕСТИРОВАНИЕ ПОТОЧНОГО ШИФРОВАНИЯ ЗАВЕРШЕНО ===" << endl;

    //Сагайдак Сергей
    std::string message = "Secret Message";
    demonstrateEncryption(message);

    // Шипкова Виктория (блочное шифрование RC6)
    string message1 = "Hello, world!";
    string message2 = "Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!Hello, world! This is my block cipher implementation program! Let's check how it works, I hope it's correct!!!";

    block_cipher_RС6(message1);
    block_cipher_RС6(message2);

    return 0;

}