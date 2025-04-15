// This program demonstrates the use of union in C++
#include <iostream>
using namespace std;
union one4all{
    int a;
    double b;
    long long c;
};
// union一次只能存放一种数据类型，不能存放不同的数据类型
int main(){
    one4all x;
    x.a = 10;
    cout<<"Value of x.a: "<<x.a<<endl;
    x.b = 20.5;
    cout<<"Value of x.b: "<<x.b<<endl;
    cout << "Value of x.a: " << x.a << endl;// Accessing the same memory location as x.b
    x.c = 30;
    cout<<"Value of x.c: "<<x.c<<endl;
    return 0;
}