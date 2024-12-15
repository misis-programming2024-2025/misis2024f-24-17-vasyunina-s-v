#ifndef RATIONAL_RATIONAL_HPP_20231113
#define RATIONAL_RATIONAL_HPP_20231113

#include <cstdint>
#include <iosfwd>

class Rational {
 public:
    Rational() = default;
    Rational(const Rational&) = default;
    explicit Rational(const std::int64_t num) noexcept : num_(num) { }
    Rational(const std::int64_t num, const std::int64_t den);
    ~Rational() = default;
    Rational& operator=(const Rational&) = default;

    std::int64_t num() const noexcept;
    std::int64_t den() const noexcept;

    bool operator==(const Rational& rhs) const noexcept;
    bool operator!=(const Rational& rhs) const noexcept;
    bool operator<(const Rational& rhs) const noexcept;
    bool operator<=(const Rational& rhs) const noexcept;
    bool operator>(const Rational& rhs) const noexcept;
    bool operator>=(const Rational& rhs) const noexcept;

    Rational operator-() const noexcept;

    Rational& operator+=(const Rational& rhs) noexcept;
    Rational& operator-=(const Rational& rhs) noexcept;
    Rational& operator*=(const Rational& rhs) noexcept;
    Rational& operator/=(const Rational& rhs);

    Rational& operator+=(const int64_t rhs) noexcept;
    Rational& operator-=(const int64_t rhs) noexcept;
    Rational& operator*=(const int64_t rhs) noexcept;
    Rational& operator/=(const int64_t rhs);

    //! \brief Форматированный вывод в поток ostrm рационального числа в виде num/den.
    //!
    //! \param[in,out] ostrm - поток
    //! \retval поток
    std::ostream& WriteTo(std::ostream& ostrm) const noexcept;

    //! \brief Форматированный ввод из потока istrm комплексного числа в виде num/den.
    //!
    //! \param[in,out] istrm - поток
    //! \retval
    std::istream& ReadFrom(std::istream& istrm) noexcept;

 private:
    std::int64_t num_ = 0;
    std::int64_t den_ = 1;
};

 Rational operator+(const Rational& lhs, const Rational& rhs) noexcept;
 Rational operator-(const Rational& lhs, const Rational& rhs) noexcept;
 Rational operator*(const Rational& lhs, const Rational& rhs) noexcept;
 Rational operator/(const Rational& lhs, const Rational& rhs);

 Rational operator+(const Rational& lhs, const int64_t rhs) noexcept;
 Rational operator-(const Rational& lhs, const int64_t rhs) noexcept;
 Rational operator*(const Rational& lhs, const int64_t rhs) noexcept;
 Rational operator/(const Rational& lhs, const int64_t rhs);

 Rational operator+(const int64_t lhs, const Rational& rhs) noexcept;
 Rational operator-(const int64_t lhs, const Rational& rhs) noexcept;
 Rational operator*(const int64_t lhs, const Rational& rhs) noexcept;
 Rational operator/(const int64_t lhs, const Rational& rhs);

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept;

std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept;

#endif