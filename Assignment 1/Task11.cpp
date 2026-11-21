//Shree Thilak Muthukrishna
#include <iostream>
#include <array>

class FareConfig {
private:
    std::array<long long, 3> f;
public:
    constexpr FareConfig(long long i, long long m, long long o) : f{i, m, o} {}

    long long get(int idx) const {
        if (idx >= 0 && idx < 3) return f[idx];
        return 0LL;
    }
};

int main() {
    constexpr FareConfig cfg(1000LL, 2000LL, 3000LL);
    std::cout << cfg.get(0) << " " << cfg.get(1) << " " << cfg.get(2) << "\n";
    return 0;
}