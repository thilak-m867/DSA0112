//Shree Thilak Muthukrishna
#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>
#include <string>

enum class Zone { Inner = 1, Middle = 2, Outer = 3 };

bool isPeak(int h, int m) {
    if (h < 0 || h > 23 || m < 0 || m > 59) return false;
    if (h >= 8 && h < 10) return true;
    if (h >= 17 && h < 20) return true;
    return false;
}

long long getFare(Zone z, int h, int m) {
    long long b = 0;
    switch (z) {
        case Zone::Inner:  b = 1000LL; break;
        case Zone::Middle: b = 2000LL; break;
        case Zone::Outer:  b = 3000LL; break;
    }
    if (isPeak(h, m)) b += (b * 20LL) / 100LL;
    return b;
}

struct Test {
    std::string tag;
    Zone z;
    int h;
    int m;
    long long exp;
};

int main() {
    std::vector<Test> ts = {
        {"T1", Zone::Inner, 12, 0, 1000LL},
        {"T2", Zone::Middle, 8, 30, 2400LL},
        {"T3", Zone::Outer, 18, 0, 3600LL},
        {"T4", Zone::Inner, 8, 0, 1200LL},
        {"T5", Zone::Inner, 10, 0, 1000LL},
        {"T6", Zone::Middle, 17, 0, 2400LL},
        {"T7", Zone::Outer, 20, 0, 3000LL}
    };

    for (const auto& t : ts) {
        long long res = getFare(t.z, t.h, t.m);
        assert(res == t.exp);
        std::cout << t.tag << " OK\n";
    }
    return 0;
}