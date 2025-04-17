#include "book.h"

namespace Library
{
    Book::Book() :  title(""), author(""), year(0) {}

    Book::Book(const std::string &t, const std::string &a, int y)
        : title(t), author(a), year(y) {}

    std::ostream& operator<<(std::ostream &os, const Book &b) {
        os << "Title: "  << b.title
           << ", Author: " << b.author
           << ", Year: "   << b.year;
        return os;
    }
    
    std::istream& operator>>(std::istream &is, Book &b) {
        std::string t, a;
        int         y;
        if (is >> t >> a >> y) {
            b.title  = t;
            b.author = a;
            b.year   = y;
        }
        return is;
    }
} // namespace Library
