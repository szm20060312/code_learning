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