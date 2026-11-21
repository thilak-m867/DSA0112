#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Time {
    int seconds;

public:
    explicit Time(int h = 0, int m = 0, int s = 0)
        : seconds(h * 3600 + m * 60 + s) {}

    Time& operator++() { // prefix ++
        ++seconds;
        return *this;
    }

    Time operator++(int) { // postfix ++
        Time copy(*this);
        ++seconds;
        return copy;
    }

    bool operator==(const Time& rhs) const { return seconds == rhs.seconds; }
    bool operator<(const Time& rhs) const { return seconds < rhs.seconds; }

    void print() const {
        int h = seconds / 3600;
        int m = (seconds % 3600) / 60;
        int s = seconds % 60;
        std::cout << h << ':' << (m < 10 ? "0" : "") << m
                  << ':' << (s < 10 ? "0" : "") << s;
    }
};

class Playlist {
    std::vector<std::string> tracks;

    void checkIndex(int i) const {
        if (i < 0 || static_cast<size_t>(i) >= tracks.size()) {
            std::cerr << "[Error] Playlist index out of range: " << i << '\n';
            throw std::out_of_range("Invalid playlist index");
        }
    }

public:
    void add(const std::string& t) { tracks.push_back(t); }
    size_t size() const { return tracks.size(); }

    std::string& operator[](int i) {
        checkIndex(i);
        return tracks[i];
    }

    const std::string& operator[](int i) const {
        checkIndex(i);
        return tracks[i];
    }
};

int main() {
    // 1. Roll-over (00:59:59 -> 1:00:00), prefix/postfix ++, and < / == checks
    Time t(0, 59, 59);
    Time a = t++;
    Time b = ++t;
    Time t2(1, 0, 1);

    std::cout << "a="; a.print();
    std::cout << " b="; b.print();
    std::cout << " t="; t.print();
    std::cout << " (a < b: " << std::boolalpha << (a < b)
              << ", b == t2: " << (b == t2) << ")\n";

    // 2. Playlist [] access (non-const & const) and out-of-range checks
    Playlist pl;
    pl.add("Intro");
    pl.add("Chorus");
    pl[1] = "Chorus (Remix)";
    const Playlist& cpl = pl;
    std::cout << "Track 0: " << cpl[0] << " | Track 1: " << pl[1] << '\n';

    try {
        std::cout << pl[-1] << '\n';
    } catch (const std::out_of_range&) {}

    try {
        std::cout << pl[static_cast<int>(pl.size())] << '\n';
    } catch (const std::out_of_range&) {}

    // 3. 10,000,000 prefix vs postfix increment timing
    const int N = 10'000'000;
    volatile int sink = 0;

    Time preTimer(0, 0, 0);
    auto s1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        ++preTimer;
    }
    auto e1 = std::chrono::high_resolution_clock::now();
    sink += (preTimer == Time(0, 0, N)) ? 1 : 0;

    Time postTimer(0, 0, 0);
    auto s2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        postTimer++;
    }
    auto e2 = std::chrono::high_resolution_clock::now();
    sink += (postTimer == Time(0, 0, N)) ? 1 : 0;
    (void)sink;

    double preMs = std::chrono::duration<double, std::milli>(e1 - s1).count();
    double postMs = std::chrono::duration<double, std::milli>(e2 - s2).count();
    std::cout << "10M prefix  (++t): " << preMs << " ms\n";
    std::cout << "10M postfix (t++): " << postMs << " ms\n";

    return 0;
}