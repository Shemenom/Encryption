#include <iostream>
#include <string>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

// сюда пишите свой алгоритм
string simpleEncrypt(const string& input) {
    string result = input;
    for (char& c : result) {
        c = c + 1;
    }
    return result;
}

// здесь пиши дешифровку
string simpleDecrypt(const string& input) {
    string result = input;
    for (char& c : result) {
        c = c - 1;
    }
    return result;
}

void testEncryption() {
    vector<string> testTexts = {
        "Hello",
        "Test message",
        "A",
        "Long text " + string(50, 'X')
    };
    
    cout << "=== Тестирование простого алгоритма ===" << endl;
    
    for (const string& text : testTexts) {
        cout << "\nТекст: \"" << text << "\"" << endl;
        
        auto start = high_resolution_clock::now();
        string encrypted = simpleEncrypt(text); 
        auto end = high_resolution_clock::now();
        long long encryptTime = duration_cast<microseconds>(end - start).count();
        
        cout << "Зашифровано: " << encrypted << endl;
        cout << "Время шифрования: " << encryptTime << " мкс" << endl;

        start = high_resolution_clock::now();
        string decrypted = simpleDecrypt(encrypted); 
        end = high_resolution_clock::now();
        long long decryptTime = duration_cast<microseconds>(end - start).count();
        
        cout << "Расшифровано: \"" << decrypted << "\"" << endl;
        cout << "Время дешифрования: " << decryptTime << " мкс" << endl;
        
        if (text == decrypted) {
            cout << "Сходится" << endl;
        } else {
            cout << "hueta" << endl;
        }
    }
}

int main() {
    testEncryption();
    return 0;
}