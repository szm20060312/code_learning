// This is an example of inline function in C++
// 内联函数
// inline function cannot recursion
#include <iostream>
inline double func(double x) {return x*x;}

int main() {
    std::cout << "The square of 5 is " << func(5) << std::endl;
    double a=13;
    std::cout << "The square of " << a << " is " << func(a++) << std::endl;
    std::cout << "Now a = " << a << std::endl;
    return 0;
}