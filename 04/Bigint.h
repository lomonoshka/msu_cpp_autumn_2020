#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include "Vector.cpp"
#include <complex>

const double PI = 3.1415926535;
using complex = std::complex<long double>;
 
const uint16_t power = 4;
const size_t base = pow(10, power);

class Bigint {
   public:
    Bigint(const std::string &str_number);
    Bigint(int);

    Bigint(const Bigint &b) = default;
    ~Bigint() = default;
    Bigint &operator=(const Bigint &rhs) = default;

    friend Bigint addition_with_absolute(const Bigint &lhs, const Bigint &rhs, bool is_positive);
    friend Bigint difference_with_absolute(const Bigint &lhs, const Bigint &rhs, bool is_positive);

    const Bigint operator-() const;
    friend Bigint operator+(const Bigint &lhs, const Bigint &rhs);
    friend Bigint operator-(const Bigint &lhs, const Bigint &rhs);
    friend Bigint operator*(const Bigint &lhs, const Bigint &rhs);
    friend Bigint operator^(Bigint lhs, size_t rhs);

    friend Bigint ffp(const Bigint &lhs, const Bigint &rhs);

    friend bool operator==(const Bigint &lhs, const Bigint &rhs);
    friend bool operator!=(const Bigint &lhs, const Bigint &rhs);
    friend bool operator>(const Bigint &lhs, const Bigint &rhs);
    friend bool operator<(const Bigint &lhs, const Bigint &rhs);
    friend bool operator>=(const Bigint &lhs, const Bigint &rhs);
    friend bool operator<=(const Bigint &lhs, const Bigint &rhs);
    friend bool abs_compare(const Bigint &lhs, const Bigint &rhs);

    friend std::ostream &operator<<(std::ostream &os, const Bigint &rhs);
    operator std::string() const;
    void remove_leading_zeros();

   private:
    Bigint() = default;

   private:
    Vector<size_t> digits_;
    bool is_positive_;
};
