#include <iostream>

struct Parcel {
    double weightKg;
    bool express;
    bool insured;
};

double charge(double weightKg, bool express = false, bool insured = false) {
    double cost = weightKg * 50.0;
    if (express) cost += 100.0;
    if (insured) cost += 40.0;
    return cost;
}

double charge(int weightGrams, bool express = false, bool insured = false) {
    return charge(weightGrams / 1000.0, express, insured);
}

double charge(const Parcel& p) {
    return charge(p.weightKg, p.express, p.insured);
}

int main() {
    Parcel box{3.5, true, true};

    std::cout << "1. charge(2.5):             " << charge(2.5) << '\n';
    std::cout << "2. charge(2.5, true):       " << charge(2.5, true) << '\n';
    std::cout << "3. charge(2.5, true, true): " << charge(2.5, true, true) << '\n';
    std::cout << "4. charge(2):               " << charge(2) << '\n';
    std::cout << "5. charge(2.0f):            " << charge(2.0f) << '\n';
    std::cout << "6. charge(box):             " << charge(box) << '\n';
    return 0;
}