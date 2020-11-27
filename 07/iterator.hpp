#include <vector>

namespace my {
template <class T>
class random_iterator : public std::iterator<std::random_access_iterator_tag, T,
                                             ptrdiff_t, T*, T&> {
   public:
    random_iterator(T* data) : data_{data} {}

    bool operator==(const random_iterator& other) {
        return data_ == other.data_;
    }

    bool operator!=(const random_iterator& other) {
        return data_ != other.data_;
    }

    bool operator<(const random_iterator& other) {
        return data_ < other.data_;
    }

    bool operator<=(const random_iterator& other) {
        return data_ <= other.data_;
    }

    bool operator>(const random_iterator& other) {
        return data_ > other.data_;
    }

    bool operator>=(const random_iterator& other) {
        return data_ >= other.data_;
    }

    random_iterator& operator++() {
        ++data_;
        return *this;
    }

    random_iterator operator++(int) {
        random_iterator old{*this};
        ++data_;
        return old;
    }

    random_iterator& operator--() {
        --data_;
        return *this;
    }

    random_iterator operator--(int) {
        random_iterator old{*this};
        --data_;
        return old;
    }

    random_iterator operator+(int shift) const {
        return {data_ + shift};
    }

    random_iterator operator-(int shift) const {
        return {data_ - shift};
    }

    random_iterator& operator+=(int shift) {
        data_ += shift;
        return *this;
    }

    random_iterator& operator-=(int shift) {
        return {data_ -= shift};
    }

    T& operator*() {
        return *data_;
    }

    const T& operator*() const {
        return *data_;
    }

   private:
    T* data_;
};
}