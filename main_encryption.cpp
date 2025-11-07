#include <iostream>
#include <chrono>
#include <functional>
#include "algorithm.h"

// это не трогать !!!
template<typename Func, typename... Args>
auto Time(Func&& func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    
    std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
    
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

int main() {
    // здесь проверяйте свой код


}