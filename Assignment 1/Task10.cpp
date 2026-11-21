//Shree Thilak Muthukrishna
#include <iostream>

int main() {
    const long long n = 3000000LL;
    long long single_p = 2600LL;
    double single_r = 26.0;

    long long tot_p = 0;
    double tot_r = 0.0;
    int tot_i = 0;

    for (long long i = 0; i < n; ++i) {
        tot_p += single_p;
        tot_r += single_r;
        tot_i += static_cast<int>(single_p);
    }

    std::cout << "ll:  " << tot_p << "\n";
    std::cout << "dbl: " << std::fixed << tot_r << "\n";
    std::cout << "int: " << tot_i << "\n";
    return 0;
}