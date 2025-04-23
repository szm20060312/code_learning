# C++ 运算符重载详解

## 📘 什么是运算符重载？

运算符重载（Operator Overloading）是 C++ 的一个强大特性，允许程序员为自定义类型（类）重新定义标准运算符（如 +、-、== 等）的行为，使它们可以直接操作类对象。

------

## 🧱 运算符重载的基本语法

```cpp
返回类型 operator运算符(参数列表);
```

- 可以是类的**成员函数**或**友元函数**。
- 成员函数：`a + b` 等价于 `a.operator+(b)`
- 友元函数：当需要访问类的私有成员，或两个操作数都不是当前类对象时使用。

------

## 📌 常见运算符重载分类及示例

以下通过一个 `Point`（二维点）类展示常用运算符的重载。

```cpp
#include <iostream>
using namespace std;

class Point {
private:
    int x, y;

public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    // 显示点
    void display() const {
        cout << "(" << x << ", " << y << ")" << endl;
    }

    // 1. 加法运算符 +
    Point operator+(const Point& p) const {
        return Point(x + p.x, y + p.y);
    }

    // 2. 赋值运算符 =
    Point& operator=(const Point& p) {
        if (this != &p) {
            x = p.x;
            y = p.y;
        }
        return *this;
    }

    // 3. 等于运算符 ==
    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }

    // 4. 前置自增 ++a
    Point& operator++() {
        ++x;
        ++y;
        return *this;
    }

    // 5. 后置自增 a++
    Point operator++(int) {
        Point temp = *this;
        x++;
        y++;
        return temp;
    }

    // 6. 负号 -a
    Point operator-() const {
        return Point(-x, -y);
    }

    // 7. 输出流 <<
    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    // 8. 输入流 >>
    friend istream& operator>>(istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }

    // 9. 小于运算符 < （以点距原点距离比较）
    bool operator<(const Point& p) const {
        return (x*x + y*y) < (p.x*p.x + p.y*p.y);
    }

    // 10. 下标运算符 []
    int& operator[](int index) {
        if (index == 0) return x;
        else return y;
    }
};
```

------

## 💻 示例用法

```cpp
int main() {
    Point a(1, 2), b(3, 4), c;

    c = a + b;             // 加法
    cout << "c = " << c << endl;

    ++a;                   // 前置++
    cout << "++a = " << a << endl;

    b++;                   // 后置++
    cout << "b++ = " << b << endl;

    cout << (a == b ? "a == b" : "a != b") << endl;

    Point d;
    cout << "请输入一个点 (x y)：";
    cin >> d;              // 输入流重载
    cout << "你输入的是：" << d << endl;

    cout << "d[0] = " << d[0] << ", d[1] = " << d[1] << endl; // 下标访问

    return 0;
}
```

------

## 📝 可重载的运算符一览

| 运算符          | 用途     | 可重载 | 说明                |
| --------------- | -------- | ------ | ------------------- |
| + - * / %       | 算术运算 | ✅      | 成员或友元          |
| == != < > <= >= | 比较     | ✅      | 成员或友元          |
| =               | 赋值     | ✅      | 建议成员函数        |
| ++ --           | 自增自减 | ✅      | 前置/后置版本要区分 |
| []              | 下标访问 | ✅      | 必须是成员函数      |
| ()              | 函数调用 | ✅      | 必须是成员函数      |
| << >>           | 输入输出 | ✅      | 通常为友元函数      |
| new delete      | 内存管理 | ✅      | 成员或友元          |

🚫 **不能重载的运算符**：

- `::` 作用域解析符
- `.` 成员访问符
- `.*` 成员指针访问符
- `sizeof`, `typeid`, `alignof`, `decltype`

------

## 🔚 总结

运算符重载是提高类使用便利性的重要手段，但也要注意：

- 保持运算符的**直觉语义**（避免混淆）
- 避免过度使用，保持代码清晰

