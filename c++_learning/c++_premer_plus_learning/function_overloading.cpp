#include <iostream>
using namespace std;

int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

int func(){
    cout<<"This is a function without any parameters."<<endl;
    return 0;
}

int func(int a){
    cout<<"This is a function with one parameter."<<endl;
    return a;
}

int main() {
    int a = 10, b = 20;
    double c = 3.14, d = 2.71;

    cout << "Sum of " << a << " and " << b << " is " << add(a, b) << endl;
    cout << "Sum of " << c << " and " << d << " is " << add(c, d) << endl;
    func();
    func(10);
    return 0;
}