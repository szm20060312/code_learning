#include <iostream>
#include <string>
using namespace std;

class Student {
    private:
        string name;
        int age;
        int id;
    
    public:
        Student(){
            name = "NONE";
            age = 0;
            id = 0;
        }
        Student(string n, int a, int i) {
            name=n;
            age=a;
            id=i;
        }
        Student(const Student& s) {
            name=s.name;
            age=s.age;
            id=s.id;
        }
        ~Student(){
            cout << "Destructor called" << endl;
        }
        void set_name(string n) {
            name = n;
        }
        void set_age(int a) {
            age = a;
        }
        void set_id(int i) {
            id = i;
        }
        string show_name() {
            return name;
        }
        int show_age() {
            return age;
        }
        int show_id() {
            return id;
        }
        void print() {
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "ID: " << id << endl;
        }
};

int main() {
    Student s1;
    s1.set_name("John");
    s1.set_age(20);
    s1.set_id(12345);
    // cout << "Name: " << s1.show_name() << endl;
    // cout << "Age: " << s1.show_age() << endl;
    // cout << "ID: " << s1.show_id() << endl;
    s1.print();
    Student s2(s1);
    // cout << "Name: " << s2.show_name() << endl;
    // cout << "Age: " << s2.show_age() << endl;
    // cout << "ID: " << s2.show_id() << endl;
    s2.print();
    Student s3("Mary", 21, 67890);
    s3.print();
    return 0;
}