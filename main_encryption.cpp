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
