#include "Bigint.h"

#include <iomanip>
#include <iostream>

bool check_string(const std::string &number) {
    if (number.empty() || (number.size() == 1 && number[0] == '-')) {
        return false;
    }
    auto it_begin = (number[0] == '-') ? next(begin(number)) : begin(number);
    auto it = std::find_if(it_begin, end(number), [](const char &c) {
        return !isdigit(c);
    });
    return it == number.end();
}

int64_t ctoi(const char *begin, const char *end) {
    int64_t result = 0;
    while (begin != end) {
        result = result * 10 + *begin - '0';
        ++begin;
    }
    return result;
}

Bigint::Bigint(const std::string &str_number) {
    if (!check_string(str_number)) {
        throw std::invalid_argument(str_number);
    } else {
        is_positive_ = str_number[0] != '-';
        auto begin_str = (is_positive_) ? str_number.c_str() : str_number.c_str() + 1;
        auto end_str = str_number.c_str() + str_number.size();

        if ((end_str - begin_str) % power == 0) {
            digits_.reserve((end_str - begin_str) / power);
        } else {
            digits_.reserve((end_str - begin_str) / power + 1);
        }

        auto pointer = end_str;
        for (pointer; pointer > begin_str + power; pointer -= power) {
            digits_.push_back(ctoi(pointer - power, pointer));
        }
        if (begin_str != pointer) {
            digits_.push_back(ctoi(begin_str, pointer));
        }
    }
}

Bigint::Bigint(int number) {
    is_positive_ = number > 0;
    number = is_positive_ ? number : -number;
    size_t length = (number == 0) ? 1u : static_cast<size_t>(log10(number) + 1);
    digits_.resize(length % power == 0 ? length / power : length / power + 1);

    for (size_t &digit : digits_) {
        digit = number % base;
        number /= base;
    }
}

std::ostream &operator<<(std::ostream &os, const Bigint &rhs) {
    if (!rhs.is_positive_) {
        os << "-";
    }
    os << rhs.digits_[rhs.digits_.size() - 1];
    for (size_t i = rhs.digits_.size() - 1; i > 0; --i) {
        os << std::setfill('0') << std::setw(power);
        os << rhs.digits_[i-1];
    }
    return os;
}

Bigint::operator std::string() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

bool operator==(const Bigint &lhs, const Bigint &rhs) {
    if (lhs.digits_.size() == 1 && lhs.digits_.size() == 1 && lhs.digits_[0] == 0 && rhs.digits_[0] == 0) {
        return true;
    }

    if (lhs.is_positive_ != rhs.is_positive_ ||
        lhs.digits_.size() != rhs.digits_.size()) {
        return false;
    }

    for (size_t i = 0; i < lhs.digits_.size(); ++i) {
        if (lhs.digits_[i] != rhs.digits_[i]) {
            return false;
        }
    }
    return true;
}

//compare two Bigint on absalute value. Return true if lhs abs(lhs) < abs(rhs)
bool abs_compare(const Bigint &lhs, const Bigint &rhs) {
    if (lhs.digits_.size() != rhs.digits_.size()) {
        return lhs.digits_.size() < rhs.digits_.size();
    } else {
        for (size_t i = lhs.digits_.size(); i > 0; --i) {
            if (lhs.digits_[i - 1] < rhs.digits_[i - 1]) {
                return true;
            }
            if (lhs.digits_[i - 1] > rhs.digits_[i - 1])
                return false;
        }
        return false;
    }
}

bool operator<(const Bigint &lhs, const Bigint &rhs) {
    if (lhs.is_positive_ != rhs.is_positive_) {
        return rhs.is_positive_;
    } else if (lhs.digits_.size() != rhs.digits_.size()) {
        return !lhs.is_positive_ ^ (lhs.digits_.size() < rhs.digits_.size());
    } else {
        return !(lhs == rhs) && (!lhs.is_positive_) ^ abs_compare(lhs, rhs);
    }
}

bool operator!=(const Bigint &lhs, const Bigint &rhs) {
    return !(lhs == rhs);
}

bool operator<=(const Bigint &lhs, const Bigint &rhs) {
    return (lhs < rhs || lhs == rhs);
}

bool operator>(const Bigint &lhs, const Bigint &rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Bigint &lhs, const Bigint &rhs) {
    return !(lhs < rhs);
}

const Bigint Bigint::operator-() const {
    Bigint result(*this);
    result.is_positive_ = !result.is_positive_;
    return result;
}

void Bigint::remove_leading_zeros() {
    while (this->digits_.size() > 1 && this->digits_.back() == 0) {
        this->digits_.pop_back();
    }
}

// These functions were created to avoid excess copy with unary operator -, for example A - (-B).
// You shouldn't use it if you just want to add or substract two Bigint, insted use euqivalent operators + and -
Bigint addition_with_absolute(const Bigint &lhs, const Bigint &rhs, bool is_positive) {
    bool res = 0;
    Bigint result;
    result.is_positive_ = is_positive;
    result.digits_.reserve(lhs.digits_.size() + 1);

    for (size_t i = 0; i < rhs.digits_.size(); ++i) {
        if (base - res - lhs.digits_[i] > rhs.digits_[i]) {
            result.digits_.push_back(lhs.digits_[i] + rhs.digits_[i] + res);
            res = 0;
        } else {
            result.digits_.push_back(lhs.digits_[i] - (base - res - rhs.digits_[i]));
            res = 1;
        }
    }
    for (size_t i = rhs.digits_.size(); i < lhs.digits_.size(); ++i) {
        if (base - res > lhs.digits_[i]) {
            result.digits_.push_back(lhs.digits_[i] + res);
            res = 0;
        } else {
            result.digits_.push_back(lhs.digits_[i] - (base - res));
        }
    }
    if (res) {
        result.digits_.push_back(res);
    }

    return result;
}

Bigint difference_with_absolute(const Bigint &lhs, const Bigint &rhs, bool is_positive) {
    bool res = 0;
    Bigint result;
    result.is_positive_ = is_positive;
    result.digits_.reserve(lhs.digits_.size());
    for (size_t i = 0; i < rhs.digits_.size(); ++i) {
        if (lhs.digits_[i] < rhs.digits_[i] + res) {
            result.digits_.push_back(lhs.digits_[i] + (base - rhs.digits_[i] - res));
            res = 1;
        } else {
            result.digits_.push_back(lhs.digits_[i] - res - rhs.digits_[i]);
            res = 0;
        }
    }
    for (size_t i = rhs.digits_.size(); i < lhs.digits_.size(); ++i) {
        if (lhs.digits_[i] < res) {
            result.digits_.push_back(base - res);
        } else {
            result.digits_.push_back(lhs.digits_[i] - res);
            res = 0;
        }
    }
    result.remove_leading_zeros();
    return result;
}

Bigint operator+(const Bigint &lhs, const Bigint &rhs) {
    if (lhs.is_positive_ == rhs.is_positive_) {
        if (lhs.digits_.size() < rhs.digits_.size()) {
            return addition_with_absolute(rhs, lhs, lhs.is_positive_);
        } else {
            return addition_with_absolute(lhs, rhs, lhs.is_positive_);
        }
    } else if (abs_compare(lhs, rhs)) {
        return difference_with_absolute(rhs, lhs, rhs.is_positive_);
    } else {
        return difference_with_absolute(lhs, rhs, lhs.is_positive_);
    }
}

Bigint operator-(const Bigint &lhs, const Bigint &rhs) {
    if (lhs.is_positive_ != rhs.is_positive_) {
        if (lhs.digits_.size() < rhs.digits_.size()) {
            return addition_with_absolute(rhs, lhs, lhs.is_positive_);
        } else {
            return addition_with_absolute(lhs, rhs, lhs.is_positive_);
        }
    } else if (abs_compare(lhs, rhs)) {
        return difference_with_absolute(rhs, lhs, !rhs.is_positive_);
    } else {
        return difference_with_absolute(lhs, rhs, lhs.is_positive_);
    }
}

int rev(int num, int lg_n) {
    int res = 0;
    for (int i = 0; i < lg_n; ++i)
        if (num & (1 << i))
            res |= 1 << (lg_n - 1 - i);
    return res;
}

void fft(Vector<complex> &a, bool invert) {
    int n = (int)a.size();
    int lg_n = 0;
    while ((1 << lg_n) < n) ++lg_n;

    for (int i = 0; i < n; ++i)
        if (i < rev(i, lg_n))
            swap(a[i], a[rev(i, lg_n)]);

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        complex wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            complex w(1);
            for (int j = 0; j < len / 2; ++j) {
                complex u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert)
        for (int i = 0; i < n; ++i)
            a[i] /= n;
}

Bigint operator*(const Bigint &lhs, const Bigint &rhs) {
    if(lhs.digits_.size() <  rhs.digits_.size()) {
        return rhs * lhs;
    }
    Bigint result;
    result.digits_.resize(lhs.digits_.size() + rhs.digits_.size() + 1);
    result.is_positive_ = lhs.is_positive_ == rhs.is_positive_;
    for (size_t i = 0; i < lhs.digits_.size(); ++i) {
        size_t res = 0;
        for (size_t j = 0; j < rhs.digits_.size(); ++j) {
            int64_t prod = res + result.digits_[i + j] + lhs.digits_[i] * rhs.digits_[j];
            result.digits_[i + j] = prod % base;
            res = prod / base;
        }
        size_t j = rhs.digits_.size();
        while(res != 0) {
            result.digits_[i + j++] = res % base;
            res /= base;
        }
    }
    result.remove_leading_zeros();
    return result;
}

Bigint ffp(const Bigint &lhs, const Bigint &rhs) {
    Vector<complex> fa(lhs.digits_.size()), fb(rhs.digits_.size());
    for (size_t i = 0; i < fa.size(); ++i) {
        fa[i] = lhs.digits_[i];
    }
    for (size_t i = 0; i < fb.size(); ++i) {
        fb[i] = rhs.digits_[i];
    }
    size_t n = 1;
    while (n < std::max(lhs.digits_.size(), rhs.digits_.size())) n <<= 1;
    n <<= 1;
    fa.resize(n), fb.resize(n);

    fft(fa, false), fft(fb, false);
    for (size_t i = 0; i < n; ++i)
        fa[i] *= fb[i];
    fft(fa, true);

    Bigint result;
    result.is_positive_ = lhs.is_positive_ == rhs.is_positive_;
    result.digits_.resize(n);
    uint64_t carry = 0;
    for (size_t i = 0; i < n; ++i) {
        uint64_t coef = static_cast<size_t>(fa[i].real() + 0.5) + carry;
        carry = coef / base;
        result.digits_[i] = coef % base;
    }
    result.remove_leading_zeros();
    return result;
}

Bigint operator^(Bigint lhs, size_t rhs) {
    Bigint result(1);
    result.is_positive_ |= rhs % 2 == 0; 
    if (rhs == 0) {
        return result;
    }
    while (rhs) {
        if (rhs % 2 == 0) {
            rhs /= 2;
            lhs = lhs * lhs;
        } else {
            --rhs;
            result = result * lhs;
        }
    }
    return result;
}