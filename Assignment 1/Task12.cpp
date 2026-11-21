//Shree Thilak Muthukrishna
#include <iostream>
#include <string>
#include <memory>
#include <utility>

enum class Zone { Inner = 0, Middle = 1, Outer = 2, Airport = 3 };
enum class Day { Mon, Tue, Wed, Thu, Fri, Sat, Sun };

struct Rates {
    static constexpr long long BASE[] = {1000LL, 2000LL, 3000LL, 6000LL};
    static constexpr int PEAK_PCT = 20;
    static constexpr int WKND_PCT = 10;
};

class Pass {
private:
    Zone za, zb;
public:
    Pass(Zone a, Zone b) : za(a), zb(b) {}
    bool valid(Zone u, Zone v) const {
        return (u == za && v == zb) || (u == zb && v == za) ||
               (u == za && v == za) || (u == zb && v == zb);
    }
};

class CardV2 {
private:
    std::string id;
    long long bal;
    std::unique_ptr<Pass> pass;
    static constexpr long long MIN_B = 5000LL;

public:
    CardV2(std::string s, long long b) : id(std::move(s)), bal(b), pass(nullptr) {}

    void setPass(std::unique_ptr<Pass> p) {
        pass = std::move(p);
    }

    long long getFare(Zone s, Zone d, int h, Day dy) const {
        if (pass && pass->valid(s, d)) return 0LL;
        Zone m = (s > d) ? s : d;
        long long f = Rates::BASE[static_cast<int>(m)];
        bool pk = (h >= 8 && h < 10) || (h >= 17 && h < 20);
        bool wk = (dy == Day::Sat || dy == Day::Sun);

        if (pk) f += (f * Rates::PEAK_PCT) / 100;
        else if (wk) f -= (f * Rates::WKND_PCT) / 100;
        return f;
    }

    bool ride(Zone s, Zone d, int h, Day dy) {
        long long f = getFare(s, d, h, dy);
        if (f == 0LL) return true;
        if ((bal - f) < MIN_B) return false;
        bal -= f;
        return true;
    }

    long long getBal() const { return bal; }
};

int main() {
    CardV2 c("U1", 6000LL);
    std::cout << c.ride(Zone::Inner, Zone::Airport, 12, Day::Sat) << " " << c.getBal() << "\n";
    c.setPass(std::make_unique<Pass>(Zone::Inner, Zone::Airport));
    std::cout << c.ride(Zone::Inner, Zone::Airport, 12, Day::Sat) << " " << c.getBal() << "\n";
    return 0;
}