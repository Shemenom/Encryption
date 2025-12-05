#include "algorithm.h"
#include <iostream>
#include <cstring>

using namespace std;

// Адаптеры для RC6
void rc6_encrypt_adapter(const vector<uint8_t>& input, vector<uint8_t>& output, const vector<uint8_t>& key) {
    RC6 cipher(key, 20);
    output = cipher.EncryptBlock(input);
}

void rc6_decrypt_adapter(const vector<uint8_t>& input, vector<uint8_t>& output, const vector<uint8_t>& key) {
    RC6 cipher(key, 20);
    output = cipher.DecryptBlock(input);
}

// Реализация ECB
ECB::ECB(void (*enc_func)(const vector<uint8_t>&, vector<uint8_t>&, const vector<uint8_t>&), 
         void (*dec_func)(const vector<uint8_t>&, vector<uint8_t>&, const vector<uint8_t>&),
         const vector<uint8_t>& key_data, int blk_size) {
    encrypt_block = enc_func;
    decrypt_block = dec_func;
    block_size = blk_size;
    key = key_data;
}

vector<uint8_t> ECB::encrypt(const vector<uint8_t>& data) {
    // Добавляем padding
    int padded_len = data.size() + (block_size - (data.size() % block_size));
    if (padded_len == data.size()) padded_len += block_size;
    
    vector<uint8_t> padded_data = data;
    uint8_t padding_value = padded_len - data.size();
    padded_data.resize(padded_len, padding_value);
    
    // Шифруем каждый блок в режиме ECB
    vector<uint8_t> ciphertext;
    for (size_t i = 0; i < padded_data.size(); i += block_size) {
        vector<uint8_t> block(padded_data.begin() + i, padded_data.begin() + i + block_size);
        vector<uint8_t> encrypted_block;
        encrypt_block(block, encrypted_block, key);
        ciphertext.insert(ciphertext.end(), encrypted_block.begin(), encrypted_block.end());
    }
    
    return ciphertext;
}

vector<uint8_t> ECB::decrypt(const vector<uint8_t>& data) {
    if (data.size() % block_size != 0) {
        throw runtime_error("Invalid ciphertext length for ECB");
    }
    
    // Дешифруем каждый блок
    vector<uint8_t> decrypted_data;
    for (size_t i = 0; i < data.size(); i += block_size) {
        vector<uint8_t> block(data.begin() + i, data.begin() + i + block_size);
        vector<uint8_t> decrypted_block;
        decrypt_block(block, decrypted_block, key);
        decrypted_data.insert(decrypted_data.end(), decrypted_block.begin(), decrypted_block.end());
    }
    
    // Убираем padding
    if (decrypted_data.empty()) return decrypted_data;
    
    uint8_t padding_value = decrypted_data.back();
    if (padding_value > block_size || padding_value == 0) {
        throw runtime_error("Invalid padding in ECB decryption");
    }
    
    // Проверяем padding
    for (size_t i = decrypted_data.size() - padding_value; i < decrypted_data.size(); ++i) {
        if (decrypted_data[i] != padding_value) {
            throw runtime_error("Invalid padding bytes in ECB decryption");
        }
    }
    
    decrypted_data.resize(decrypted_data.size() - padding_value);
    return decrypted_data;
}

// Тестовая функция
void test_ecb_rc6(const string& input_str, const vector<uint8_t>& key) {
    cout << "Исходная строка: '" << input_str << "'" << endl;
    
    // Создаем ECB с адаптерами RC6
    ECB ecb(rc6_encrypt_adapter, rc6_decrypt_adapter, key, 16);
    
    // Преобразуем строку в байты
    vector<uint8_t> plaintext(input_str.begin(), input_str.end());
    
    // Шифруем
    vector<uint8_t> ciphertext;
    try {
        ciphertext = ecb.encrypt(plaintext);
        cout << "Зашифровано: ";
        for (size_t i = 0; i < ciphertext.size() && i < 16; ++i) {
            printf("%02X ", ciphertext[i]);
        }
        if (ciphertext.size() > 16) cout << "...";
        cout << endl;
    } catch (const exception& e) {
        cout << "Ошибка шифрования: " << e.what() << endl;
        return;
    }
    
    // Дешифруем
    vector<uint8_t> decrypted;
    try {
        decrypted = ecb.decrypt(ciphertext);
        string result(decrypted.begin(), decrypted.end());
        cout << "Расшифровано: '" << result << "'" << endl;
        
        // Проверяем совпадение
        if (plaintext == decrypted) {
            cout << "✅ Строки совпадают!" << endl;
        } else {
            cout << "❌ Строки не совпадают!" << endl;
        }
    } catch (const exception& e) {
        cout << "Ошибка дешифрования: " << e.what() << endl;
    }
    
    cout << endl;
}