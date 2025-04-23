#include <iostream>

class Person{
public:
    Person(){
        std::cout<<"Default constructor called"<<std::endl;
    }
    Person(int age,int height){
        std::cout<<"Parameterized constructor called"<<std::endl;
        m_age = age;
        m_height = new int(height);
    
    }
    Person(const Person& p){
        std::cout<<"Copy constructor called"<<std::endl;
        m_age = p.m_age;
        m_height = new int(*p.m_height);
    }
    ~Person(){
        std::cout<<"Destructor called"<<std::endl;
        if(m_height!=nullptr){
            delete m_height;
            m_height = nullptr;
        }
    }
public:
    int m_age;
    int* m_height;
};
void test(){
    Person p1(18,170);
    Person p2(p1); // copy constructor is called here
    std::cout << "p1 age: " << p1.m_age << std::endl;
    std::cout << "p1 height: " << *p1.m_height << std::endl;
    std::cout << "p2 age: " << p2.m_age << std::endl;
    std::cout << "p2 height: " << *p2.m_height << std::endl;
    std::cout << "----------------------------------" << std::endl;
    p1.m_age = 20;
    p1.m_height=new int(175);
    std::cout << "p1 age: " << p1.m_age << std::endl;
    std::cout << "p1 height: " << *p1.m_height << std::endl;
    std::cout << "p2 age: " << p2.m_age << std::endl;
    std::cout << "p2 height: " << *p2.m_height << std::endl;
    std::cout << "----------------------------------" << std::endl;
    p2.m_age = 25;
    p2.m_height=new int(180);
    std::cout << "p1 age: " << p1.m_age << std::endl;
    std::cout << "p1 height: " << *p1.m_height << std::endl;
    std::cout << "p2 age: " << p2.m_age << std::endl;
    std::cout << "p2 height: " << *p2.m_height << std::endl;
}
int main(){
    test();
    return 0;
}

