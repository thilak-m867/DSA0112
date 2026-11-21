//Shree Thilak Muthukrishna
#include <iostream>
#include <cassert>
#include <string>
#include <utility>

class Card {
private:
    std::string id;
    long long bal;
    static constexpr long long MIN_B = 5000LL;

public:
    Card(std::string s, long long b) : id(std::move(s)), bal(b) {}

    bool canGo(long long f) const {
        return (bal - f) >= MIN_B;
    }

    bool pay(long long f) {
        if (!canGo(f)) return false;
        bal -= f;
        return true;
    }

    long long getBal() const { return bal; }
};

int main() {
    Card c("C1", 6000LL);
    assert(c.canGo(1000LL));
    assert(c.pay(1000LL));
    assert(c.getBal() == 5000LL);
    assert(!c.canGo(1000LL));
    assert(!c.pay(1000LL));
    std::cout << c.getBal() << "\n";
    return 0;
}