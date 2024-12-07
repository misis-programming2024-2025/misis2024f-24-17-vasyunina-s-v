#include <complex.hpp>
#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <limits>

const double EPSILON = std::numeric_limits<double>::epsilon() * 2;


bool testConstructor(double re, double im) {
    Complex complex(re, im);
    return complex == Complex(re, im); 
}

bool testEquality() {
    Complex a(1.0, 1.0);
    Complex b(1.0 + EPSILON / 2, 1.0); 
    Complex c(1.0 + EPSILON * 2, 1.0); 
    return (a == b) && (a != c); 
}

bool testOperatorPlus() {
    Complex a(2.0, 5.0);
    Complex b(3.0, 4.0);
    return (a + b) == Complex(5.0, 9.0);
}

bool testOperatorMinus() {
    Complex a(5.0, 7.0);
    Complex b(3.0, 6.0);
    return (a - b) == Complex(2.0, 2.0);
}

bool testOperatorMultiply() {
    Complex a(5.0, 4.0);
    Complex b(2.0, 3.0);
    return (a * b) == Complex(23.0, -12.0);
}

bool testOperatorDivide() {
    Complex a(1.0, 2.0);
    Complex b(3.0, 4.0);
    return (a / b) == Complex(0.44, 0.08);
}

bool testOperatorInput() {
    Complex a;
    std::istringstream input("{1.0,2.0}");
    input >> a;
    return a == Complex(1.0, 2.0); 
}

bool testOperatorOutput() {
    Complex a(1.0, 2.0);
    std::ostringstream output;
    output << std::fixed << std::setprecision(1) << a; 
    return output.str() == "{1.0,2.0}"; 
}

int main() {
    std::cout << "Test Constructor: " 
              << (testConstructor(1.2, 4.3) ? "Passed" : "Failed") << std::endl;

    std::cout << "Test Operator ==: " 
              << (testEquality() ? "Passed" : "Failed") << std::endl;

    std::cout << "Test Operator +: " 
              << (testOperatorPlus() ? "Passed" : "Failed") << std::endl;

    std::cout << "Test Operator -: " 
              << (testOperatorMinus() ? "Passed" : "Failed") << std::endl;

    std::cout << "Test Operator *: " 
              << (testOperatorMultiply() ? "Passed" : "Failed") << std::endl;

    std::cout << "Test Operator /: " 
              << (testOperatorDivide() ? "Passed" : "Failed") << std::endl;

    std::cout << "Test Operator >>: " 
              << (testOperatorInput() ? "Passed" : "Failed") << std::endl;

    std::cout << "Test Operator <<: " 
              << (testOperatorOutput() ? "Passed" : "Failed") << std::endl;

}