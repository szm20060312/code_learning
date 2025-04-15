#include <iostream>
#include <iomanip>
using namespace std;
double x,y,a,b;
//double z;
int main() {
    cin >> x >> a >> y >> b;
    cout<<fixed<<setprecision(2)<<(x*a-y*b)/(a-b)<<endl;
    return 0;
}