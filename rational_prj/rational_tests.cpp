#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <stdexcept>
#include <iostream>
#include "rational/rational.hpp"

// Тест конструктора с двумя аргументами (числитель и знаменатель)
TEST_CASE("Rational constructor with two arguments") {
    Rational r(5, 2);
    CHECK(r.num() == 5);
    CHECK(r.den() == 2);  // дробь 5/2
}

//Тест конструктора, когда знаменатель ноль
TEST_CASE("Test constructor throws exception when denominator is zero") {
    CHECK_THROWS_AS(Rational(3, 0), std::invalid_argument);
}

TEST_CASE("Rational copy constructor") {
    Rational r1(5, 2);
    Rational r2 = r1;  
    CHECK(r2.num() == r1.num());
    CHECK(r2.den() == r1.den());
}

TEST_CASE("Rational equality operator") {
    Rational r1(5, 2);
    Rational r2(5, 2);
    CHECK(r1 == r2);

    Rational r3(3, 2);
    CHECK(r1 != r3);
}

TEST_CASE("Rational inequality operator") {
    Rational r1(5, 2);
    Rational r2(3, 2);
    CHECK(r1 != r2);
}

TEST_CASE("Rational less than operator") {
    Rational r1(5, 2);
    Rational r2(3, 2);
    CHECK(r1 > r2);
    CHECK(r2 < r1);
}

TEST_CASE("Rational less than or equal operator") {
    Rational r1(5, 2);
    Rational r2(5, 2);
    CHECK(r1 <= r2);

    Rational r3(7, 2);
    CHECK(r1 <= r3);
}

TEST_CASE("Rational greater than operator") {
    Rational r1(5, 2);
    Rational r2(3, 2);
    CHECK(r1 > r2);
    CHECK_FALSE(r2 > r1);
}

TEST_CASE("Rational greater than or equal operator") {
    Rational r1(5, 2);
    Rational r2(5, 2);
    CHECK(r1 >= r2);

    Rational r3(3, 2);
    CHECK(r1 >= r3);
}

TEST_CASE("Rational negation operator") {
    Rational r1(5, 2);
    Rational r2 = -r1;
    CHECK(r2.num() == -5);
    CHECK(r2.den() == 2);
}

TEST_CASE("Rational plus equal operator(Rational += Rational)") {
    Rational r1(5, 2);
    Rational r2(1, 2);
    r1 += r2;
    CHECK(r1.num() == 6);
    CHECK(r1.den() == 2); 
}

TEST_CASE("Rational minus equal operator(Rational -= Rational)") {
    Rational r1(5, 2);
    Rational r2(3, 2);
    r1 -= r2;
    CHECK(r1.num() == 2);
    CHECK(r1.den() == 2);  
}

TEST_CASE("Rational multiply equal operator(Rational *= Rational)") {
    Rational r1(5, 2);
    Rational r2(2, 3);
    r1 *= r2;
    CHECK(r1.num() == 10);
    CHECK(r1.den() == 6); 
}

TEST_CASE("Rational divide equal operator(Rational /= Rational)") {
    Rational r1(5, 2);
    Rational r2(2, 3);
    r1 /= r2;
    CHECK(r1.num() == 15);
    CHECK(r1.den() == 4); 
}

TEST_CASE("Rational plus equal operator(Rational += int)") {
    Rational r(5, 2);
    r += 2; 
    CHECK(r.num() == 9);
    CHECK(r.den() == 2);
}

TEST_CASE("Rational minus equal operator(Rational -= int)") {
    Rational r(5, 2);
    r -= 1;
    CHECK(r.num() == 3);
    CHECK(r.den() == 2);
}

TEST_CASE("Rational multiply equal operator(Rational *= int)") {
    Rational r(5, 2);
    r *= 3;  
    CHECK(r.num() == 15);
    CHECK(r.den() == 2);
}

TEST_CASE("Rational divide equal operator(Rational /= int)") {
    Rational r(5, 2);
    r /= 2;  
    CHECK(r.num() == 5);
    CHECK(r.den() == 4);
}


TEST_CASE("Rational stream output operator") {
    Rational r(5, 2);
    std::ostringstream ostrm;
    ostrm << r;
    CHECK(ostrm.str() == "5/2");  
}


TEST_CASE("Rational stream input operator") {
    std::istringstream istrm("3/4");
    Rational r;
    istrm >> r;
    CHECK(r.num() == 3);
    CHECK(r.den() == 4);
}

TEST_CASE("Rational WriteTo method") {
    Rational r(5, 2);
    std::ostringstream ostrm;
    r.WriteTo(ostrm);
    CHECK(ostrm.str() == "5/2");
}

TEST_CASE("Rational ReadFrom method") {
    std::istringstream istrm("7/3");
    Rational r;
    r.ReadFrom(istrm);
    CHECK(r.num() == 7);
    CHECK(r.den() == 3);
}

TEST_CASE("Rational addition operator (Rational)") {
    Rational r1(5, 2);
    Rational r2(1, 2);
    Rational result = r1 + r2;
    CHECK(result.num() == 6);
    CHECK(result.den() == 2);
}

TEST_CASE("Rational subtraction operator (Rational)") {
    Rational r1(5, 2);
    Rational r2(3, 2);
    Rational result = r1 - r2;
    CHECK(result.num() == 2);
    CHECK(result.den() == 2); 
}

TEST_CASE("Rational multiplication operator (Rational)") {
    Rational r1(5, 2);
    Rational r2(2, 3);
    Rational result = r1 * r2;
    CHECK(result.num() == 10);
    CHECK(result.den() == 6); 
}

TEST_CASE("Rational division operator (Rational)") {
    Rational r1(5, 2);
    Rational r2(2, 3);
    Rational result = r1 / r2;
    CHECK(result.num() == 15);
    CHECK(result.den() == 4); 
}

TEST_CASE("Rational addition operator (Rational + int)") {
    Rational r(5, 2);
    Rational result = r + 2;
    CHECK(result.num() == 9);
    CHECK(result.den() == 2);  
}

TEST_CASE("Rational subtraction operator (Rational - int)") {
    Rational r(5, 2);
    Rational result = r - 1;
    CHECK(result.num() == 3);
    CHECK(result.den() == 2);
}


TEST_CASE("Rational multiplication operator (Rational * int)") {
    Rational r(5, 2);
    Rational result = r * 3;
    CHECK(result.num() == 15);
    CHECK(result.den() == 2);  
}

TEST_CASE("Rational division operator (Rational / int)") {
    Rational r(5, 2);
    Rational result = r / 2;
    CHECK(result.num() == 5);
    CHECK(result.den() == 4); 
}

TEST_CASE("Rational addition operator (int + Rational)") {
    Rational r(5, 2);
    Rational result = 3 + r;
    CHECK(result.num() == 11);
    CHECK(result.den() == 2); 
}

TEST_CASE("Rational subtraction operator (int - Rational)") {
    Rational r(5, 2);
    Rational result = 7 - r;
    CHECK(result.num() == 9);
    CHECK(result.den() == 2); 
}

TEST_CASE("Rational multiplication operator (int * Rational)") {
    Rational r(5, 2);
    Rational result = 3 * r;
    CHECK(result.num() == 15);
    CHECK(result.den() == 2); 
}

TEST_CASE("Rational division operator (int / Rational)") {
    Rational r(5, 2);
    Rational result = 6 / r;
    CHECK(result.num() == 12);
    CHECK(result.den() == 5); 
}

TEST_CASE("Test input stream with invalid input") {
    std::stringstream ss_cerr;
    std::streambuf* original_cerr = std::cerr.rdbuf();
    std::cerr.rdbuf(ss_cerr.rdbuf());

    std::istringstream iss("3/0");
    Rational r;

    iss >> r;

    // Проверяем, что в std::cerr записано сообщение об ошибке
    CHECK(ss_cerr.str() == "Error: invalid input for denominator\n");

    // Восстанавливаем оригинальный поток ошибок
    std::cerr.rdbuf(original_cerr);
}
