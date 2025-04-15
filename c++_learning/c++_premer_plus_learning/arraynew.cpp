// using the new operactor for arrays
#include <iostream>
using namespace std;

int main() {
    double * p3 = new double[10];
    p3[0] = 0.2;
    p3[1] = 0.5;
    p3[2] = 0.8;
    cout << "p3[1] = " << p3[1] << endl;
    p3+=1; // move pointer to next element
    cout << "now p3[0] = " << p3[0] << endl;
    cout << "now p3[1] = " << p3[1] << endl;
    p3-=1; // move pointer back to previous element
    delete[] p3;
    return 0;
}