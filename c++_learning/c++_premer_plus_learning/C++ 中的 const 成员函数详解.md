# C++ 中的 const 成员函数详解

## ✅ 什么是 const 成员函数？

const 成员函数是类中的一种特殊函数，**承诺不会修改对象的成员变量**（除了被声明为 `mutable` 的变量）。

### 📌 定义格式：

```cpp
返回类型 函数名(参数列表) const;
```

------

## 🔍 特性一览

| 特性         | 描述                                        |
| ------------ | ------------------------------------------- |
| 关键字位置   | 定义函数时加在函数签名后面                  |
| 对象类型限制 | 只能被 const 对象调用                       |
| 成员访问限制 | 不能修改非 mutable 成员变量                 |
| this 指针    | 在 const 成员函数中为 const ClassName* 类型 |

------

## 📦 示例代码：

```cpp
class Point {
private:
    int x, y;

public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    void display() const {  // ✅ const 成员函数
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

int main() {
    const Point p(3, 4);
    p.display();      // ✅ OK：const 函数可以调用
    // p.move(1, 1);   // ❌ 错误：不能调用非 const 函数
}
```

------

## 🚧 为什么 const 对象不能调用普通成员函数？

```cpp
const Point p;
p.move(1, 1);   // ❌ 编译错误
```

这是因为：

- `p` 是一个 const 对象，不能修改其状态。
- `move()` 函数不是 const 函数，**可能会修改对象状态**。
- 所以编译器为了安全，**禁止调用**。

✅ 只有 const 成员函数能保证不修改对象状态，因此才能被 const 对象调用。

------

## 🔁 const 成员函数中的行为

```cpp
void display() const {
    // this 的类型是 const Point*，不允许修改 x, y
    // x = 10;   // ❌ 错误：不能修改数据成员
}
```

------

## 🔓 特例：mutable 成员变量

```cpp
class Timer {
private:
    mutable int accessCount; // 可以在 const 函数中修改

public:
    void log() const {
        ++accessCount; // ✅ 合法
    }
};
```

`mutable` 关键字允许该变量在 const 函数中被修改。

------

## 🧠 总结表

| 情况                             | 是否允许               |
| -------------------------------- | ---------------------- |
| const 对象调用 const 成员函数    | ✅ 允许                 |
| const 对象调用普通成员函数       | ❌ 禁止                 |
| const 成员函数修改成员变量       | ❌ 禁止（除非 mutable） |
| 非 const 对象调用 const 成员函数 | ✅ 允许                 |

------

## 💡 类比记忆法：

> `const` 成员函数 = 图书馆阅览区，只能看，不能带走或涂改📚🔒。

------

继续学习推荐：`mutable` 关键字、重载 const 与非 const 函数、const 在运算符重载中的应用。