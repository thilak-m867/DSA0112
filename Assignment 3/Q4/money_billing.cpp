#include <iomanip>
#include <iostream>

class Money {
    long long paise;

public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    // TODO 1: Overload + as a member function that returns a new Money object
    Money operator+(const Money& rhs) const {
        Money res;
        res.paise = this->paise + rhs.paise;
        return res;
    }

    // TODO 2: Overload == as a member, and << as a friend that prints "Rs 200.00"
    bool operator==(const Money& rhs) const {
        return this->paise == rhs.paise;
    }

    Money operator-(const Money& rhs) const {
        Money res;
        res.paise = this->paise - rhs.paise;
        return res;
    }

    Money& operator+=(const Money& rhs) {
        this->paise += rhs.paise;
        return *this;
    }

    bool operator<(const Money& rhs) const {
        return this->paise < rhs.paise;
    }

    friend std::ostream& operator<<(std::ostream& os, const Money& m) {
        long long absPaise = m.paise < 0 ? -m.paise : m.paise;
        long long r = absPaise / 100;
        int p = static_cast<int>(absPaise % 100);
        if (m.paise < 0) os << '-';
        os << "Rs " << r << '.' << std::setw(2) << std::setfill('0') << p;
        return os;
    }
};

int main() {
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    std::cout << c << '\n' << std::boolalpha << (c == Money(200)) << '\n';

    Money carry = Money(0, 75) + Money(0, 50);
    std::cout << "Carry test: " << carry << '\n';
    return 0;
}