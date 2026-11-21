#include <chrono>
#include <iostream>

class ShiftingAccount {
    static const int K = 200;
    double transactions[K];
    int count = 0;
public:
    void record(double amt) {
        if (count < K) {
            transactions[count] = amt;
        } else {
            for (int i = 1; i < K; ++i) transactions[i - 1] = transactions[i];
            transactions[K - 1] = amt;
        }
        ++count;
    }
    double latest() const { return transactions[(count < K ? count : K) - 1]; }
};

class CircularAccount {
    static const int K = 200;
    double transactions[K];
    int head = 0;
    int size = 0;
public:
    void record(double amt) {
        if (size < K) {
            transactions[(head + size) % K] = amt;
            ++size;
        } else {
            transactions[head] = amt;
            head = (head + 1) % K;
        }
    }
    double latest() const {
        int lastIdx = (head + size - 1) % K;
        return transactions[lastIdx];
    }
};

int main() {
    const int N = 1'000'000;
    ShiftingAccount orig;
    CircularAccount redesign;

    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= N; ++i) orig.record(i * 1.5);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto t3 = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= N; ++i) redesign.record(i * 1.5);
    auto t4 = std::chrono::high_resolution_clock::now();

    double origMs = std::chrono::duration<double, std::milli>(t2 - t1).count();
    double redesignMs = std::chrono::duration<double, std::milli>(t4 - t3).count();

    std::cout << "Original Shifting Account (1M txns, K=200):   " << origMs
              << " ms (latest=" << orig.latest() << ")\n";
    std::cout << "Redesigned Circular Account (1M txns, K=200): " << redesignMs
              << " ms (latest=" << redesign.latest() << ")\n";
    std::cout << "Speedup Factor: " << (origMs / redesignMs) << "x faster\n";
    return 0;
}