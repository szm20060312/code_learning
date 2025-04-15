#include <iostream>
/*用户输入两个物体的半径和质量
用户可以自定义两物体之间的距离
程序分别计算万有引力和坍缩成中子星的临界质量
*/
double G = 6.67408e-11; // 单位为 N*m^2/kg^2
long long p=1000000000000000000; // 单位为 10^18
long double pi=3.14159265;

//计算万有引力(现在接受距离参数)
double calcGravitationalForce(double r1, double m1, double r2, double m2, double d) {
    double force = G * m1 * m2 / pow(d,2); //万有引力
    return force;
}

// 计算中子星坍缩质量(不变)
// 注意：这里假设有一个函数用来计算中子星的临界质量，但具体实现并未在代码中给出
double calcCriticalNeutronStarMass(double R) {
    // 这里应该填写计算中子星临界质量的逻辑
    long double V=(4/3)*pi*pow(R,3); // 单位为 m^3
    long double M=p*V; // 单位为 kg
    return M;

}

int main() {
    int m1,m2,r1,r2,d;
    std::cout<<"Enter the mass and radius of the first object: ";
    std::cin>>m1>>r1;
    std::cout<<"Enter the mass and radius of the second object: ";
    std::cin>>m2>>r2;
    std::cout<<"Enter the distance between the two objects: ";
    std::cin>>d;
    double R = r1 + r2 + d; //两物体之间的距离
    double force = calcGravitationalForce(r1, m1, r2, m2, R);

    double criticalMass = calcCriticalNeutronStarMass(R);

    std::cout<<"The gravitational force between the two objects is "<<force<<std::endl;
    std::cout<<"The critical mass of the neutron star is "<<criticalMass<<std::endl;
    return 0;
}