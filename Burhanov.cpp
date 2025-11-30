#include "aes.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    string a(1000, '0');
    string b(1000000, '0');
    test_encryption("Hello, World!", "mysecretkey");
    cout << endl;
    test_encryption(a, "mysecretkey");
    cout << endl;
    test_encryption(b, "mysecretkey");
    return 0;
}
