#include <iostream>

int my_strlen_recursive(const char *str) {
    if (str[0] == '\0') {
        return 0;
    }
    return 1 + my_strlen_recursive(str + 1);
}

int main() {
    const char *testStr = "Hello, World!";
    std::cout << "Length of string: " << my_strlen_recursive(testStr) << std::endl;
    return 0;
}