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
    // здесь проверяйте свой код
    cout << "=== ТЕСТИРОВАНИЕ СИСТЕМЫ ELGAMAL ===" << endl << endl;

    vector<long long> small_numbers = { 1, 42, 100, 255, 512, 999, 1024, 2048 };
    test_small_numbers(small_numbers);

    vector<long long> huge_numbers = { 1000000000, 2500000000 };
    test_huge_numbers(huge_numbers);

    cout << "=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===" << endl;

    return 0;

}

long long ElGamalUniversal::mod_pow(long long base, long long exponent, long long mod) {
    if (mod == 1) return 0;
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

bool ElGamalUniversal::is_prime(long long n, int iterations) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;

    uniform_int_distribution<long long> dis(2, n - 2);
    long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    for (int i = 0; i < iterations; i++) {
        long long a = dis(gen);
        long long x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (int j = 0; j < r - 1; j++) {
            x = (x * x) % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

long long ElGamalUniversal::generate_prime(long long min_val, long long max_val) {
    uniform_int_distribution<long long> dis(min_val, max_val);
    int attempts = 0;
    while (attempts < 5000) {
        long long candidate = dis(gen);
        if (candidate % 2 == 0) candidate++;

        for (int i = 0; i < 500; i++) {
            if (candidate > max_val) break;
            if (is_prime(candidate)) {
                return candidate;
            }
            candidate += 2;
        }
        attempts++;
    }
    return 0; 
}

long long ElGamalUniversal::find_primitive_root(long long p) {
    if (p == 2) return 1;
    long long phi = p - 1;
    vector<long long> factors;

    long long n = phi;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) factors.push_back(n);

    for (long long g = 2; g < p; g++) {
        bool ok = true;
        for (long long factor : factors) {
            if (mod_pow(g, phi / factor, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
    return 2;
}

long long ElGamalUniversal::gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

ElGamalUniversal::ElGamalUniversal(string size) : gen(rd()) {
    if (size == "small") {
        p = generate_prime(1000, 10000);
    }
    else if (size == "huge") {
        p = generate_prime(1000000000, 5000000000);
    }
    else {
        p = generate_prime(10000, 100000);
    }

    if (p == 0) {
        cout << "Ошибка: не удалось сгенерировать простое число" << endl;
        return;
    }

    g = find_primitive_root(p);
    uniform_int_distribution<long long> dis(2, p - 2);
    x = dis(gen);  
    y = mod_pow(g, x, p); 
}

pair<long long, long long> ElGamalUniversal::encrypt_number(long long number) {
    if (number >= p) {
        cout << "Ошибка: число " << number << " слишком большое. Максимум: " << (p - 1) << endl;
        return make_pair(0, 0);
    }

    long long k;
    uniform_int_distribution<long long> dis(2, p - 2);
    do {
        k = dis(gen);
    } while (gcd(k, p - 1) != 1);

    long long a = mod_pow(g, k, p);
    long long b = (number * mod_pow(y, k, p)) % p;

    return make_pair(a, b);
}

long long ElGamalUniversal::decrypt_number(pair<long long, long long> ciphertext) {
    long long a = ciphertext.first;
    long long b = ciphertext.second;

    if (a == 0 && b == 0) {
        cout << "Ошибка: некорректный шифротекст" << endl;
        return -1;
    }

    long long s = mod_pow(a, x, p);
    long long s_inv = mod_pow(s, p - 2, p);
    long long message = (b * s_inv) % p;

    return message;
}

void ElGamalUniversal::print_info() {
    cout << "Параметры системы ElGamal:" << endl;
    cout << "p: " << p << " (максимальное число: " << (p - 1) << ")" << endl;
    cout << "g: " << g << endl;
    cout << "x: " << x << " (закрытый ключ)" << endl;
    cout << "y: " << y << " (открытый ключ)" << endl;
    cout << "----------------------------" << endl;
}

bool ElGamalUniversal::is_valid() {
    return p != 0;
}

void test_small_numbers(const vector<long long>& numbers_to_encrypt) {
    cout << "=== ТЕСТ МАЛЕНЬКИХ ЧИСЕЛ ===" << endl;

    ElGamalUniversal crypto("small");

    crypto.print_info();

    for (long long number : numbers_to_encrypt) {
        auto encrypted = crypto.encrypt_number(number);

        if (encrypted.first == 0 && encrypted.second == 0) {
            continue;
        }

        long long decrypted = crypto.decrypt_number(encrypted);

        if (number == decrypted) {
            cout << number << " → (" << encrypted.first << ", " << encrypted.second << ")" << endl;
        }
        else {
            cout << "ОШИБКА: " << number << " → " << decrypted << endl;
        }
    }
    cout << endl;
}

void test_huge_numbers(const vector<long long>& numbers_to_encrypt) {
    cout << "=== ТЕСТ БОЛЬШИХ ЧИСЕЛ ===" << endl;

    ElGamalUniversal crypto("huge");
    if (!crypto.is_valid()) {
        cout << "Ошибка создания криптосистемы" << endl;
        return;
    }

    crypto.print_info();

    for (long long number : numbers_to_encrypt) {
        auto encrypted = crypto.encrypt_number(number);

        if (encrypted.first == 0 && encrypted.second == 0) {
            continue;
        }

        long long decrypted = crypto.decrypt_number(encrypted);

        if (number == decrypted) {
            cout << number << " → (" << encrypted.first << ", " << encrypted.second << ")" << endl;
        }
        else {
            cout << "ОШИБКА: " << number << " → " << decrypted << endl;
        }
    }
    cout << endl;
}

