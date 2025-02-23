#include "complex.hpp"
#include <stdexcept>
#include <iomanip>
#include <cmath>

const double EPSILON = std::numeric_limits<double>::epsilon() * 2;


Complex::Complex(const double re, const double im)
    : re(re), im(im)
{}

Complex::Complex(const Complex& other) : re(other.re), im(other.im) {}

Complex& Complex::operator+=(const Complex& rhs) {
    re += rhs.re;
    im += rhs.im;
    return *this;
}

Complex& Complex::operator-=(const Complex& rhs) {
    re -= rhs.re;
    im -= rhs.im;
    return *this;
}

Complex& Complex::operator*=(const Complex& rhs) {
    double tempRe = re * rhs.re - im * rhs.im;
    im = re * rhs.im + im * rhs.re;
    re = tempRe;
    return *this;
}

Complex& Complex::operator/=(const Complex& rhs) {
    double denominator = rhs.re * rhs.re + rhs.im * rhs.im;
    if (denominator == 0.0) {
        throw std::runtime_error("Division by zero in complex division");
    }
    double tempRe = (re * rhs.re + im * rhs.im) / denominator;
    im = (im * rhs.re - re * rhs.im) / denominator;
    re = tempRe;
    return *this;
}

Complex& Complex::operator+=(double rhs) {
    re += rhs;
    return *this;
}

Complex& Complex::operator-=(double rhs) {
    re -= rhs;
    return *this;
}

Complex& Complex::operator*=(double rhs) {
    re *= rhs;
    im *= rhs;
    return *this;
}

Complex& Complex::operator/=(double rhs) {
    if (rhs == 0.0) {
        throw std::runtime_error("Division by zero in scalar division");
    }
    re /= rhs;
    im /= rhs;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Complex& z) {
    return z.writeTo(out);
}

std::istream& operator>>(std::istream& in, Complex& z) {
    return z.readFrom(in);
}

std::ostream& Complex::writeTo(std::ostream& ostrm) const {
    ostrm << std::fixed << std::setprecision(1) << leftBrace << re << separator << im << rightBrace;
    return ostrm;
}

std::istream& Complex::readFrom(std::istream& istrm) {
    char leftBraceCheck{ 0 };
    char separatorCheck{ 0 };
    char rightBraceCheck{ 0 };
    double real{ 0.0 }, imag{ 0.0 };
    istrm >> leftBraceCheck >> real >> separatorCheck >> imag >> rightBraceCheck;
    re = real;
    im = imag;
    return istrm;
}

Complex operator+(const Complex& lhs, const Complex& rhs) {
    Complex result(lhs);
    result += rhs;
    return result;
}

Complex operator-(const Complex& lhs, const Complex& rhs) {
    Complex result(lhs);
    result -= rhs;
    return result;
}

Complex operator*(const Complex& lhs, const Complex& rhs) {
    Complex result(lhs);
    result *= rhs;
    return result;
}

Complex operator/(const Complex& lhs, const Complex& rhs) {
    Complex result(lhs);
    result /= rhs;
    return result;
}

Complex operator+(const Complex& lhs, const double rhs) {
    Complex result(lhs);
    result += rhs;
    return result;
}

Complex operator-(const Complex& lhs, const double rhs) {
    Complex result(lhs);
    result -= rhs;
    return result;
}

Complex operator*(const Complex& lhs, const double rhs) {
    Complex result(lhs);
    result *= rhs;
    return result;
}

Complex operator/(const Complex& lhs, const double rhs) {
    Complex result(lhs);
    result /= rhs;
    return result;
}

bool areEqual(double a, double b) {
    return std::abs(a - b) < EPSILON;
}

bool operator==(const Complex& lhs, const Complex& rhs) {
    return areEqual(lhs.re, rhs.re) && areEqual(lhs.im, rhs.im);
}

bool operator!=(const Complex& lhs, const Complex& rhs) {
    return !(lhs == rhs);
}

//новые методы
Complex conjugate(const Complex& lhs) {
  return Complex(lhs.re, -lhs.im); //возвращает сопряженное комплексное число(a + b*i -> a - b*i)
}
double magnitude(const Complex& lhs) {
  return std::sqrt(lhs.re * lhs.re + lhs.im * lhs.im); // возвращает модуль комплексного числа
}
