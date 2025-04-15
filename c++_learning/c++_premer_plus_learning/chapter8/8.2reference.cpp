// reference is a pointer that can be used to refer to an object without creating a new object.
#include <iostream>
using namespace std;

int main() {
    int x = 5;
    cout << "x = " << x << endl; // output: x = 5
    int& ref = x; // reference to x
    ref = 10; // changing the value of x through the reference
    cout << "x = " << x << endl; // output: x = 10
    cout << "ref = " << ref << endl; // output: ref = 10
    cout << "&ref = " << &ref << endl; 
    cout << "&x = " << &x << endl; 
    return 0;
}