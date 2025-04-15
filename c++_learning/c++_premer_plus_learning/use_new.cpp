// This code demonstrates the use of the new operator in C++ to allocate memory dynamically.
// typeName * pointerName = new typeName;
#include <iostream>
using namespace std;

int* func(){
    int *p = new int(10);
    return p;
}
int main() {
    // Create objects in the heap area.
    int ptr = *func();
    cout << "The value of ptr is: " << ptr << endl;
    // Delete the object from the heap area.
    delete func();

    int nights = 1001;
    int *pt = new int;
    *pt = 1001;

    cout << "The value of nights is: " << nights << endl;
    cout << nights << ":location " << &nights << endl;
    cout << "int ";
    cout << "value = " << *pt << ": location = " << pt << endl;
    double *pd = new double;
    *pd = 3.1415926;
    cout << "double ";
    cout << "value = " << *pd << ": location = " << pd << endl;
    cout << "location of pointer pd: " << &pd << endl;
    cout << "size of pt: " << sizeof(pt) << endl;
    cout << "size of *pt: " << sizeof(*pt) << endl;
    cout << "size of pd: " << sizeof(pd) << endl;
    cout << "size of *pd: " << sizeof(*pd) << endl;
    delete pt;
    return 0;
}