#include <iostream>
#include <climits>
#include <cstddef>

int main() {
    std::cout << "C++ 数据类型存储范围验证：" << std::endl;
    std::cout << "=========================================" << std::endl;

    // int 类型范围
    std::cout << "int 类型：" << std::endl;
    std::cout << "  最小值: " << INT_MIN << std::endl;
    std::cout << "  最大值: " << INT_MAX << std::endl;
    std::cout << "  存储大小: " << sizeof(int) << " 字节" << std::endl;
    std::cout << std::endl;

    // long 类型范围
    std::cout << "long 类型：" << std::endl;
    std::cout << "  最小值: " << LONG_MIN << std::endl;
    std::cout << "  最大值: " << LONG_MAX << std::endl;
    std::cout << "  存储大小: " << sizeof(long) << " 字节" << std::endl;
    std::cout << std::endl;

    // unsigned int 类型范围
    std::cout << "unsigned int 类型：" << std::endl;
    std::cout << "  最小值: " << 0U << std::endl;
    std::cout << "  最大值: " << UINT_MAX << std::endl;
    std::cout << "  存储大小: " << sizeof(unsigned int) << " 字节" << std::endl;
    std::cout << std::endl;

    // unsigned long 类型范围
    std::cout << "unsigned long 类型：" << std::endl;
    std::cout << "  最小值: " << 0UL << std::endl;
    std::cout << "  最大值: " << ULONG_MAX << std::endl;
    std::cout << "  存储大小: " << sizeof(unsigned long) << " 字节" << std::endl;
    std::cout << std::endl;

    // 实际测试边界值
    std::cout << "实际测试边界值：" << std::endl;
    std::cout << "=========================================" << std::endl;

    // 测试 int 边界
    int int_max = INT_MAX;
    int int_min = INT_MIN;
    std::cout << "int 最大值 + 1 = " << (int_max + 1) << " (溢出变成最小值)" << std::endl;
    std::cout << "int 最小值 - 1 = " << (int_min - 1) << " (溢出变成最大值)" << std::endl;

    // 测试 unsigned int 边界
    unsigned int uint_max = UINT_MAX;
    unsigned int uint_min = 0;
    std::cout << "unsigned int 最大值 + 1 = " << (uint_max + 1) << " (溢出变成0)" << std::endl;
    std::cout << "unsigned int 最小值 - 1 = " << (uint_min - 1) << " (溢出变成最大值)" << std::endl;

    return 0;
}