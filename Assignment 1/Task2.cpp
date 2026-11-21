//Shree Thilak Muthukrishna
#include <iostream>

enum class Zone { Inner = 1, Middle = 2, Outer = 3 };

namespace Fares {
    constexpr long long I = 1000LL;
    constexpr long long M = 2000LL;
    constexpr long long O = 3000LL;
    constexpr int P_PCT = 20;
    constexpr long long MIN_BAL = 5000LL;
}

int main() {
    std::cout << Fares::I << " " << Fares::M << " " << Fares::O << "\n";
    return 0;
} 