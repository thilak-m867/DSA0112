#include <chrono>
#include <cstring>
#include <iostream>

class Text {
    char* data;
    size_t len;

public:
    Text(const char* s = "") {
        len = std::strlen(s);
        data = new char[len + 1];
        std::memcpy(data, s, len + 1);
    }

    Text(const Text& other) {
        len = other.len;
        data = new char[len + 1];
        std::memcpy(data, other.data, len + 1);
    }

    Text& operator=(const Text& other) {
        if (this == &other) return *this;
        char* fresh = new char[other.len + 1];
        std::memcpy(fresh, other.data, other.len + 1);
        delete[] data;
        data = fresh;
        len = other.len;
        return *this;
    }

    ~Text() {
        delete[] data;
    }

    Text operator+(const Text& rhs) const {
        Text combined;
        delete[] combined.data;
        combined.len = len + rhs.len;
        combined.data = new char[combined.len + 1];
        std::memcpy(combined.data, data, len);
        std::memcpy(combined.data + len, rhs.data, rhs.len + 1);
        return combined;
    }

    bool operator!=(const Text& rhs) const {
        return std::strcmp(data, rhs.data) != 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Text& t) {
        return os << t.data;
    }
};

int main() {
    Text empty("");
    Text a("SMS:");
    Text b("Hi");
    Text c("!");

    a = a; // self-assignment
    Text msg = a + b + c;
    std::cout << "Empty: [" << empty << "] | Msg: " << msg
              << " | Diff: " << std::boolalpha << (a != b) << '\n';
    return 0;
}