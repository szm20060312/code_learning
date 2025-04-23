#include <iostream>
const double PI = 3.14159265358979323846;
class Circle{
    private:

        
    public:
        int m_r;
        double calculateCircumference(){
            return 2*PI*m_r;
     }

};

int main(){
    Circle c1;
    c1.m_r = 5;
    std::cout<<"Circumference of circle with radius "<<c1.m_r<<" is "<<c1.calculateCircumference()<<std::endl;
    Circle c2;
    c2.m_r = 10;
    std::cout<<"Circumference of circle with radius "<<c2.m_r<<" is "<<c2.calculateCircumference()<<std::endl;
    return 0;
}