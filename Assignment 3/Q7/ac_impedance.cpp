#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

class Complex {
    double re;
    double im;

public:
    Complex(double r = 0.0, double i = 0.0) : re(r), im(i) {}

    double real() const { return re; }
    double imag() const { return im; }
    double magnitude() const { return std::hypot(re, im); }

    Complex operator+(const Complex& rhs) const {
        return Complex(re + rhs.re, im + rhs.im);
    }

    Complex operator-(const Complex& rhs) const {
        return Complex(re - rhs.re, im - rhs.im);
    }

    Complex operator*(const Complex& rhs) const {
        return Complex(re * rhs.re - im * rhs.im, re * rhs.im + im * rhs.re);
    }

    Complex operator/(const Complex& rhs) const {
        double denom = rhs.re * rhs.re + rhs.im * rhs.im;
        if (denom == 0.0) {
            throw std::domain_error("Division by zero impedance");
        }
        return Complex((re * rhs.re + im * rhs.im) / denom,
                       (im * rhs.re - re * rhs.im) / denom);
    }

    bool operator==(const Complex& rhs) const {
        return std::fabs(re - rhs.re) < 1e-9 && std::fabs(im - rhs.im) < 1e-9;
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& z) {
        os << std::fixed << std::setprecision(2) << z.re;
        if (z.im >= 0.0) os << " + " << z.im << "j";
        else os << " - " << (-z.im) << "j";
        return os;
    }
};

int main() {
    Complex zR(10.0, 0.0);
    Complex zL(0.0, 15.0);
    Complex zC(0.0, -5.0);

    Complex zSeries = zR + zL + zC;
    std::cout << "Series Z: " << zSeries << " | |Z|: " << zSeries.magnitude() << '\n';

    Complex zParallel = (zR * zL) / (zR + zL);
    std::cout << "Parallel Z: " << zParallel << " | |Z_par|: " << zParallel.magnitude() << '\n';

    try {
        Complex zero(0.0, 0.0);
        Complex bad = zR / zero;
        std::cout << bad << '\n';
    } catch (const std::domain_error& e) {
        std::cout << "Handled division by zero safely: " << e.what() << '\n';
    }
    return 0;
}