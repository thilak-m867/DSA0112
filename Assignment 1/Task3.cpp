//Shree Thilak Muthukrishna
#include <iostream>
#include <climits>

int main() {
    long long p_bal = 10000000LL;
    double r_bal = 100000.0;
    long long p_add = 10LL;
    double r_add = 0.10;

    for (int i = 0; i < 1000000; ++i) {
        p_bal += p_add;
        r_bal += r_add;
    }

    std::cout << p_bal << "\n";
    std::cout << std::fixed << r_bal << "\n";
    std::cout << sizeof(int) << " " << sizeof(long long) << "\n";
    return 0;
}