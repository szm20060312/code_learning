#include <iostream>
using namespace std;

class MyDynamicArray {
private:
    int* arr;   // 指向动态分配数组的指针
    int size;   // 数组的大小

public:
    // 构造函数
    MyDynamicArray(int s) : size(s) {
        arr = new int[size];  // 动态分配内存
        for (int i = 0; i < size; i++) {
            arr[i] = 0;  // 初始化数组元素
        }
    }

    // 析构函数
    ~MyDynamicArray() {
        delete[] arr;  // 释放动态分配的内存
    }

    // 下标运算符重载：用于访问和修改数组元素
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of range");
        }
        return arr[index];
    }

    // 获取数组大小
    int getSize() const {
        return size;
    }

    // 打印数组元素
    void print() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    MyDynamicArray myArr(5);  // 创建一个大小为 5 的动态数组
    
    // 通过下标运算符修改元素
    myArr[0] = 10;
    myArr[1] = 20;

    // 打印数组内容
    myArr.print();  // 输出：10 20 0 0 0 

    return 0;
}
