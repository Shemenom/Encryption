#include <iostream>
#include <chrono>
#include <functional>
#include "Dolgacheva.cpp"
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
    // это тоже не трогать !!!
    cout << "=== ТЕСТИРОВАНИЕ СИСТЕМЫ ELGAMAL ===" << endl << endl;

    vector<long long> small_numbers = { 1, 42, 100, 255, 512, 999, 1024, 2048 };
    test_small_numbers(small_numbers);

    vector<long long> huge_numbers = { 1000000000, 2500000000 };
    test_huge_numbers(huge_numbers);

    cout << "=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===" << endl;

    // Долгачева Александра
    cout << "\n=== ТЕСТИРОВАНИЕ ПОТОЧНОГО ШИФРОВАНИЯ ===" << endl;
    demonstrate_stream_cipher();
    test_stream_performance();

    return 0;

}