#include <iostream>
#include <stdexcept>
#include <string>

class Book {
    std::string title;
    std::string author;
    int copies;

    static int validateCopies(int c) {
        if (c < 0) {
            throw std::invalid_argument("Copies cannot be negative");
        }
        return c;
    }

public:
    Book() : Book("Untitled", "Unknown", 0) {}
    explicit Book(const std::string& t) : Book(t, "Unknown", 1) {}
    Book(const std::string& t, const std::string& a, int c)
        : title(t), author(a), copies(validateCopies(c)) {}

    void print() const {
        std::cout << "Title: " << title << " | Author: " << author
                  << " | Copies: " << copies << '\n';
    }
};

int main() {
    Book emptyBook;
    Book donatedBook("Clean Code");
    Book catalogBook("C++ Primer", "Lippman", 5);

    emptyBook.print();
    donatedBook.print();
    catalogBook.print();

    try {
        Book invalid("Bad Record", "Anon", -3);
    } catch (const std::exception& ex) {
        std::cout << "Caught expected error: " << ex.what() << '\n';
    }
    return 0;
}