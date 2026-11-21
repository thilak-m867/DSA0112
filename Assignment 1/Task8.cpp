//Shree Thilak Muthukrishna
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

long long getVal(const std::string& msg) {
    long long v;
    while (true) {
        std::cout << msg;
        if (std::cin >> v) return v;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void printRcpt(const std::string& id, long long f, long long b) {
    std::cout << std::left << std::setw(10) << id << " "
              << f / 100 << "." << std::setw(2) << std::setfill('0') << f % 100 << " "
              << std::setfill(' ') << b / 100 << "."
              << std::setw(2) << std::setfill('0') << b % 100 << "\n";
}

int main() {
    long long b = 10000;
    long long f = 3600;
    printRcpt("C101", f, b - f);
    return 0;
}