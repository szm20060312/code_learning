#include <iostream>
#include "book.h"

int main() {
    Library::Book b;
    std::cout << "请输入书名、作者和年份：";
    std::cin  >> b;
    std::cout << "你输入的图书信息是：\n" << b << std::endl;
    return 0;
}
