#include <chrono>
#include <cstdlib>
#include <iostream>

class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend inline int minutesBetween(const Time& a, const Time& b);
    friend inline bool earlier(const Time& a, const Time& b);
};

inline int minutesBetween(const Time& a, const Time& b) {
    // TODO 1: Using the private members h and m, return the absolute difference between
    // the two times in minutes
    int totalA = a.h * 60 + a.m;
    int totalB = b.h * 60 + b.m;
    return std::abs(totalA - totalB);
}

inline bool earlier(const Time& a, const Time& b) {
    // TODO 2: Return true if a is earlier in the day than b
    return (a.h * 60 + a.m) < (b.h * 60 + b.m);
}

int main() {
    Time departure(9, 45), arrival(13, 10);
    std::cout << minutesBetween(departure, arrival) << ' '
              << std::boolalpha << earlier(arrival, departure) << '\n';

    Time t1(11, 50), t2(12, 15), t3(11, 50);
    std::cout << "Across noon (11:50 vs 12:15): diff=" << minutesBetween(t1, t2)
              << ", earlier=" << earlier(t1, t2) << '\n';
    std::cout << "Same time (11:50 vs 11:50):   diff=" << minutesBetween(t1, t3)
              << ", earlier=" << earlier(t1, t3) << '\n';

    const int CALLS = 10'000'000;
    volatile long long sink = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < CALLS; ++i) {
        sink += minutesBetween(departure, arrival);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(end - start).count();
    std::cout << "10,000,000 calls time: " << ms << " ms\n";
    return 0;
}