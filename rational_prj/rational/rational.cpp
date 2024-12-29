#include "rational.hpp"
#include <iostream>

//нод
std::int64_t gcd(std::int64_t a, std::int64_t b) {
    a = std::abs(a);
    b = std::abs(b);
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
//конструктор
Rational::Rational(const std::int64_t num, const std::int64_t den){
    if (den == 0){
        throw std::invalid_argument("Denominator cannot be zero");
    }
    std::int64_t gcd_value = gcd(num, den);
    if (den < 0){
        num_ = -num / gcd_value;
        den_ = std::abs(den) / gcd_value;
    }
    else{
        num_ = num / gcd_value;
        den_ = den / gcd_value;
    }
}

//доступ к числителю
std::int64_t Rational::num() const noexcept{
    return num_;
}

//доступ к знаменателю
std::int64_t Rational::den() const noexcept{
    return den_;
}

//операторы сравнения(сравнивается искомый объект класса с новым передаваемым объектом)
bool Rational::operator==(const Rational& rhs) const noexcept{
    return num_*rhs.den_ == den_ * rhs.num_;
}
bool Rational::operator!=(const Rational& rhs) const noexcept{
    return num_*rhs.den_ != den_ * rhs.num_;
}
bool Rational::operator<(const Rational& rhs) const noexcept{
    return num_*rhs.den_ < den_ * rhs.num_;
}
bool Rational::operator<=(const Rational& rhs) const noexcept{
    return num_*rhs.den_ <= den_ * rhs.num_;
}
bool Rational::operator>(const Rational& rhs) const noexcept{
    return num_*rhs.den_ > den_ * rhs.num_;
}
bool Rational::operator>=(const Rational& rhs) const noexcept{
    return num_*rhs.den_ >= den_ * rhs.num_;
}

// нахождение противоположного числа
Rational Rational::operator-() const noexcept {
    return Rational(-num_, den_);
}

//арифметические операции(имеется объект класса и к нему прибавляется другой объект этого же класса)
Rational& Rational::operator+=(const Rational& rhs) noexcept{
    std::int64_t new_num = this->num_ * rhs.den_ + this->den_ * rhs.num_;
    std::int64_t new_den = this->den_ * rhs.den_;
    std::int64_t nod = gcd(new_num, new_den);
    this->num_ = new_num / nod;
    this->den_ = new_den / nod;
    return *this;
};
Rational& Rational::operator-=(const Rational& rhs) noexcept{
    std::int64_t new_num = this->num_ * rhs.den_ - this->den_ * rhs.num_;
    std::int64_t new_den = this->den_ * rhs.den_;
    std::int64_t nod = gcd(new_num, new_den);
    this->num_ = new_num / nod;
    this->den_ = new_den / nod;
    return *this;
};
Rational& Rational::operator*=(const Rational& rhs) noexcept{
    std::int64_t new_num = this->num_ * rhs.num_;
    std::int64_t new_den = this->den_ * rhs.den_;
    std::int64_t nod = gcd(new_num, new_den);
    this->num_ = new_num / nod;
    this->den_ = new_den / nod;
    return *this;
};
Rational& Rational::operator /=(const Rational& rhs){
    if (rhs.den_ == 0){
        throw std::invalid_argument("Denominator cannot be zero");
    }
    std::int64_t new_num = this->num_ * rhs.den_;
    std::int64_t new_den = this->den_ * rhs.num_;
    std::int64_t nod = gcd(new_num, new_den);
    if (new_den < 0){
        this->num_ = -new_num / nod;
        this->den_ = std::abs(new_den) / nod;
    }
    else{
        this->num_ = new_num / nod;
        this->den_ = new_den / nod;
    }
    return *this;
};

//арифметические операции(объект класс и рациональное число)
Rational& Rational::operator+=(const int64_t rhs) noexcept{
    this->num_ += rhs*this->den_;
    return *this;
}
Rational& Rational::operator-=(const int64_t rhs) noexcept{
    this->num_ -= rhs*this->den_;
    return *this;
}
Rational& Rational::operator*=(const int64_t rhs) noexcept{
    std::int64_t new_num = this->num_ * rhs;
    std::int64_t nod = gcd(new_num, this->den_);
    this->num_ = new_num / nod;
    this->den_ /= nod;
    return *this;
}
Rational& Rational::operator/=(const int64_t rhs) {
    if (rhs == 0){
        throw std::invalid_argument("Division by zero is undefined");
    }
    std::int64_t new_den = this->den_ * rhs;
    std::int64_t nod = gcd(new_den, this->num_);
    if (new_den < 0){
        this->num_ /= -nod;
        this->den_ = std::abs(new_den) / nod;
    }
    else{
        this->num_ /= nod;
        this->den_ = new_den / nod;
    }
    return *this;
}

//чтение
std::istream& Rational::ReadFrom(std::istream& istrm) noexcept {
    istrm >> num_;
    if (istrm.fail()) {
        std::cerr << "Error: invalid input for num_" << std::endl;
        return istrm; 
    }
    char ch;
    istrm >> ch;
    if (istrm.fail() || ch != '/'){
        std::cerr << "Error: you should use \"/\" between num_ and den_"<<std::endl;
        return istrm;
    }
    istrm >> den_;
    if (istrm.fail() || den_ == 0) {
        std::cerr << "Error: invalid input for denominator" << std::endl;
        return istrm;
    }
    std::int64_t nod = gcd(num_, den_);

    num_ = (den_ > 0 ? num_ / nod : -num_ / nod);
    den_ = std::abs(den_) / nod;
    return istrm;
}

//запись
std::ostream& Rational::WriteTo(std::ostream& ostrm) const noexcept {
    ostrm << num_ << "/" << den_;
    return ostrm;
}

//арифметические операции между двумя объектами класса
Rational operator+(const Rational& lhs, const Rational& rhs) noexcept {
    Rational ans = lhs;
    ans += rhs;
    return ans;
}
Rational operator-(const Rational& lhs, const Rational& rhs) noexcept {
    Rational ans = lhs;
    ans -= rhs;
    return ans;
}
Rational operator*(const Rational& lhs, const Rational& rhs) noexcept {
    Rational ans = lhs;
    ans *= rhs;
    return ans;
}
Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational ans = lhs;
    ans /= rhs;
    return ans;
}

//арифметические операцие между созданным объектом класса и рациональным числом
Rational operator+(const Rational& lhs, const int64_t rhs) noexcept {
    Rational ans = lhs;
    ans += rhs;
    return ans;
}
Rational operator-(const Rational& lhs, const int64_t rhs) noexcept {
    Rational ans = lhs;
    ans -= rhs;
    return ans;
}
Rational operator*(const Rational& lhs, const int64_t rhs) noexcept {
    Rational ans = lhs;
    ans *= rhs;
    return ans;
}
Rational operator/(const Rational& lhs, const int64_t rhs) {
    if (rhs == 0){
        throw std::invalid_argument("Denominator cannot be zero");
    }
    Rational ans = lhs;
    ans /= rhs;
    return ans;
}

//арифметические операции между рацмональным числом и созданным оъектом класса
Rational operator+(const int64_t lhs, const Rational& rhs) noexcept {
    Rational ans = rhs;
    ans += lhs;
    return ans;
}
Rational operator-(const int64_t lhs, const Rational& rhs) noexcept {
    Rational ans = rhs;
    ans = -ans;
    ans += lhs;
    return ans;
}
Rational operator*(const int64_t lhs, const Rational& rhs) noexcept {
    Rational ans = rhs;
    ans *= lhs;
    return ans;
}
Rational operator/(const int64_t lhs, const Rational& rhs) {
    Rational ans = Rational(lhs);
    ans /= rhs;
    return ans;
}

//ввод и вывод
std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept {
    return rhs.WriteTo(ostrm);
}
std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept {
    if (!rhs.ReadFrom(istrm)) {
        std::cerr << "Error: incorrect input"<<std::endl;
    }
    return istrm;
}