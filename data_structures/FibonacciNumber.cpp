#include <iostream>
using namespace std;

int FibonacciNumber(int n) {
    if (n <= 1)
        return n;
    return FibonacciNumber(n - 1) + FibonacciNumber(n - 2);
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Fibonacci series: ";
    for(int i = 0; i < n; i++){
        cout << FibonacciNumber(i) << " ";
    }
    cout << endl;
    return 0;
}