#include <iostream>
using namespace std;

class MyArray{
private:
    int arr[10];

public:
    MyArray(){
        for(int i=0;i<10;i++) arr[i]=0;
    }
    int& operator[](int index){
        if(index<0||index>=10){
            throw out_of_range("Index out of range");
        }
        return arr[index];
    }
    void print(){
        for(int i=0;i<10;i++){
            cout<<arr[i]<<" ";
        }
        cout << endl;
    }
};

int main(){
    MyArray a;
    a[0]=5;
    a[1]=10;
    a.print();
}