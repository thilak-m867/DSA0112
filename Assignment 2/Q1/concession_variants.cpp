#include <iostream>

void applyByValue(long long fee, int percent) {
    fee -= fee * percent / 100;
}

void applyByReference(long long& fee, int percent) {
    fee -= fee * percent / 100;
}

void applyByPointer(long long* fee, int percent) {
    if (fee != nullptr) {
        *fee -= (*fee) * percent / 100;
    }
}

int main() {
    long long hostelFee = 45000;
    applyByValue(hostelFee, 10);
    std::cout << "After call by value (10%):     " << hostelFee << '\n';

    applyByReference(hostelFee, 10);
    std::cout << "After call by reference (10%): " << hostelFee << '\n';

    applyByPointer(&hostelFee, 15);
    std::cout << "After call by pointer (15%):   " << hostelFee << '\n';
    return 0;
}