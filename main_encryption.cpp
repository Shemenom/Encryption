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
    // Хлебников Матвей
    cout << "=== ТЕСТИРОВАНИЕ СИСТЕМЫ ELGAMAL ===" << endl << endl;

    vector<long long> small_numbers = { 1, 42, 100, 255, 512, 999, 1024, 2048 };
    vector<long long> huge_numbers = { 1000000000, 1500000000 };

    cout << Time(test_small_numbers, small_numbers).count() << " - время выполнения в мкс" << endl;
    cout << Time(test_huge_numbers, huge_numbers).count() << " - время выполнения в мкс" << endl;

    cout << "=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===" << endl;

    /// Александра Долгачева - тестирование поточного шифрования ARC4
    cout << "\n=== ТЕСТИРОВАНИЕ ПОТОЧНОГО ШИФРОВАНИЯ (ARC4) ===" << endl;

    string message9 = "Secret Message";
    string message_1111(1000, '0');
    string message_2222(1000000, '0');

    cout << Time(demonstrateStreamCipher, message9).count() << " - время выполнения в мкс"<< endl;
    cout << Time(demonstrateStreamCipher, message_1111).count() << " - время выполнения в мкс"<< endl;
    cout << Time(demonstrateStreamCipher, message_2222).count() << " - время выполнения в мкс"<< endl;

    cout << "=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===\n\n";

    //Сагайдак Сергей
    string message_0 = "Secret Message";
    string message_1(1000, '0');
    string message_2(1000000, '0');

    cout << Time(demonstrateEncryption, message_0).count() << " - время выполнения в мкс"<< endl;
    cout << Time(demonstrateEncryption, message_1).count() << " - время выполнения в мкс"<< endl;
    cout << Time(demonstrateEncryption, message_2).count() << " - время выполнения в мкс"<< endl;

    // Шипкова Виктория (блочное шифрование RC6)
    string message1 = "Hello, world!";
    string message2(1000, '0');
    string message3(1000000, '0');
    cout << Time(block_cipher_RC6,message1).count() << " - время выполнения в мкс"<< endl;;
    cout << Time(block_cipher_RC6,message2).count() << " - время выполнения в мкс"<< endl;;
    cout << Time(block_cipher_RC6,message2).count() << " - время выполнения в мкс"<< endl;;

    
    // Бардин Глеб
    cout << "\n=== ТЕСТИРОВАНИЕ АЛГОРИТМА RSA \n";
    string text(1000000, '0');
    string text2(1000, '0');
    pair<long long, long long> publicKey = make_pair(0, 0);
    pair<long long, long long> privateKey = make_pair(0, 0);

    cout << Time(processRSA, "HELLO WORLD", publicKey, privateKey).count() << " - время выполнения в мкс"<< endl;
    cout << Time(processRSA, text2, publicKey, privateKey).count() << " - время выполнения в мкс"<< endl;
    cout << Time(processRSA, text, publicKey, privateKey).count() << " - время выполнения в мкс"<< endl;

    cout << "=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===\n\n";

    // Бурханов Тахир
    cout << "=== ТЕСТИРОВАНИЕ AES === \n";

    string a(1000, '0');
    string b(1000000, '0');
    cout << Time(test_encryption,"Hello, World!", "mysecretkey").count() << " - время выполнения в мск \n"<< endl;
    cout << Time(test_encryption, a, "mysecretkey").count() << " - время выполнения в мск \n" << endl;
    cout << Time(test_encryption, b, "mysecretkey").count() << " - время выполнения в мск \n"<< endl;

    cout << "=== КОНЕЦ ТЕСТИРОВАНИЕ AES ===\n"; 

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
    
    string message_123(1000000, '0');
    string message_121212(1000, '0');

    cout << Time(test_ecb_rc6,"Hello, World!", key16).count() << " - время выполнения в мкс \n"<< endl;
    cout << Time(test_ecb_rc6, "Short", key32).count() << " - время выполнения в мкс \n" << endl;
    cout << Time(test_ecb_rc6, message_123, key24).count() << " - время выполнения в мкс \n"<< endl; 

    return 0;
}