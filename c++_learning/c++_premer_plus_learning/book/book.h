#ifndef BOOK_H
#define BOOK_H
#include <cstring>
#include <iostream>

namespace Library{
    class Book{
        private:
        std::string title;
        std::string author;
        int year;

        public:
        Book();
        Book(const std::string &t, const std::string &a, int y);

        std::string getTitle() const {return title;}
        std::string getAuther() const {return author;}
        int getYear() const {return year;}

        friend std::ostream& operator<<(std::ostream &os, const Book &b);
        friend std::istream& operator>>(std::istream &is, Book &b);
    };
}

#endif