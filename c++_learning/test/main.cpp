#include <iostream>
#include "a.h"
#include "a.cpp"
using namespace A;
using namespace std;

int main() 
{
    double m, r;

    // 提示用户输入天体质量和半径
    cout << "请输入天体的质量（kg）: ";
    cin >> m;
    cout << "请输入天体的半径（m）: ";
    cin >> r;

    // 计算表面重力加速度和逃逸速度
    double g = Gravitational_Acceleration(m, r);
    double v_e = Escape_Velocity(r,m);

    cout << "\n该天体表面重力加速度为: " << g << " m/s2" << endl;
    cout << "该天体的逃逸速度为: " << v_e << " m/s" << endl;

    return 0;
}
