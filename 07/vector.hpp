#pragma once
#include <initializer_list>
#include <iostream>
#include <regex>
#include "allocator.hpp"
#include "iterator.hpp"

namespace my {
template <class T, class Allocator = my::allocator<T>>
class vector {
   public:
    // types
    using value_type = T;
    using allocator_type = Allocator;
    using pointer = typename allocator<value_type>::pointer;
    using const_pointer = typename allocator<value_type>::const_pointer;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;
    using iterator = my::random_iterator<T>;
    using const_iterator = const my::random_iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // utility functions for Allocator
    template <typename... Args>
    void fill(pointer begin, pointer end, Args&&... args) {
        for (pointer i = begin; i != end; ++i) {
            alloc_.construct(i, args...);
        }
    }

    void erase(pointer begin, pointer end) {
        for (pointer i = begin; i != end; ++i) {
            alloc_.destroy(i);
        }
    }

    // construct/copy/destroy
    constexpr vector() = default;

    constexpr explicit vector(size_type size, const Allocator& Alloc = Allocator())
        : alloc_(Alloc),
          data_(alloc_.allocate(size)),
          capacity_(size),
          size_(0) {
        fill(data_, data_ + size);
    };

    constexpr vector(size_type size, const T& value, const Allocator& Alloc = Allocator())
        : alloc_(Alloc),
          data_(alloc_.allocate(size)),
          capacity_(size),
          size_(size) {
        fill(data_, data_ + size, value);
    }

    constexpr vector(const vector& other)
        : alloc_(),
          data_(alloc_.allocate(other.capacity_)),
          capacity_(other.capacity_),
          size_(other.size_) {
        // copy(other.data_, other.data_ + size_, data_) - было
        for (size_type i = 0; i < size_; ++i) {
            alloc_.construct(data_+ i, other[i]);
        }
    };

    constexpr vector(vector&& other) noexcept
        : alloc_(),
          data_(other.data_),
          capacity_(other.capacity_),
          size_(other.size_) {
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    };

    constexpr vector(std::initializer_list<T>&& list, const Allocator& Alloc = Allocator())
        : alloc_(Alloc),
          data_(alloc_.allocate(std::size(list))),
          capacity_(std::size(list)),
          size_(std::size(list)) {
        size_type i = 0;
        for (auto val : list) {
            alloc_.construct(data_+ i++, std::move(val));
        }
    };

    ~vector() {
        erase(data_, data_ + capacity_);
        alloc_.deallocate(data_, capacity_);
        size_ = 0;
        capacity_ = 0;
    };

    constexpr vector& operator=(const vector& other) {
        if (data_ != other.data_) {
            if (other.size_ <= capacity_) {
                std::copy(other.data_, other.data_ + other.size_, data_);
                size_ = other.size_;
            } else {
                vector tmp(other);
                std::swap(tmp.data_, data_);
                std::swap(tmp.capacity_, capacity_);
                std::swap(tmp.size_, size_);
            }
        }
        return *this;
    }
    constexpr vector& operator=(vector&& other) {
        if (data_ != other.data_) {
            erase(data_, data_ + capacity_);
            alloc_.deallocate(data_, capacity_);
            data_ = std::exchange(other.data_, nullptr);
            size_ = std::exchange(other.size_, 0);
            capacity_ = std::exchange(other.capacity_, 0);
        }
        return *this;
    }

    constexpr vector& operator=(std::initializer_list<T>&& list) {
        if (std::size(list) <= capacity_) {
            std::move(list.begin(), list.end(), data_);
            size_ = std::size(list);
        } else {
            vector tmp(list);
            std::swap(tmp.data_, data_);
            std::swap(tmp.capacity_, capacity_);
            std::swap(tmp.size_, size_);
        }
        return *this;
    }

    // iterators
    constexpr iterator begin() noexcept {
        return iterator(data_);
    }

    constexpr const_iterator begin() const noexcept {
        return iterator(data_);
    }

    constexpr iterator end() noexcept {
        return iterator(data_ + size_);
    }

    constexpr const_iterator end() const noexcept {
        return iterator(data_ + size_);
    }

    constexpr reverse_iterator rbegin() noexcept {
        return reverse_iterator(data_ + size_);
    }

    constexpr const_reverse_iterator rbegin() const noexcept {
        return reverse_iterator(data_ + size_);
    }

    constexpr reverse_iterator rend() noexcept {
        return reverse_iterator(data_);
    }

    constexpr const_reverse_iterator rend() const noexcept {
        return reverse_iterator(data_);
    }

    // capacity
    [[nodiscard]] constexpr bool empty() const noexcept {
        return size_ == 0;
    }

    constexpr size_type size() const noexcept {
        return size_;
    }

    constexpr size_type capacity() const noexcept {
        return capacity_;
    }

    constexpr void resize(size_type size, const T& value = T()) {
        if (capacity_ < size) {
            reserve(size);
            fill(data_ + size_, data_ + size, value);
        }
        size_ = size;
    }

    constexpr void reserve(size_type capacity) {
        if (capacity > capacity_) {
            vector tmp(capacity);
            std::move(data_, data_ + size_, tmp.data_);
            std::swap(data_, tmp.data_);
            std::swap(capacity_, tmp.capacity_);
        }
    }

    void clear() noexcept {
        erase(data_, data_ + size_);
    }

    // element access
    constexpr reference operator[](size_type n) {
        return *(data_ + n);
    }

    constexpr const_reference operator[](size_type n) const {
        return *(data_ + n);
    }

    constexpr const_reference at(size_type n) const {
        if (n >= size_) {
            throw std::out_of_range("Index is out of range");
        } else {
            return *(data_ + n);
        }
    }

    constexpr reference at(size_type n) {
        if (n >= size_) {
            throw std::out_of_range("Index is out of range");
        } else {
            return *(data_ + n);
        }
    }

    constexpr reference front() {
        return *data_;
    }

    constexpr const_reference front() const {
        return *data_;
    }

    constexpr reference back() {
        return *(data_ + size_ - 1);
    }

    constexpr const_reference back() const {
        return *(data_ + size_ - 1);
    }

    // modifiers
    template <class... Args>
    constexpr reference emplace_back(Args&&... args) {
        if (size_ == capacity_) {
            reserve(capacity_ ? capacity_ * 2 : 1);
        }
        alloc_.destroy(data_ + size_);
        alloc_.construct(data_ + size_++, T(std::forward<Args>(args)...));
        return back();
    }

    constexpr void push_back(const T& value) {
        if (size_ == capacity_) {
            reserve(capacity_ ? capacity_ * 2 : 1);
        }
        alloc_.destroy(data_ + size_);
        alloc_.construct(data_ + size_++, value);
    }

    constexpr void push_back(T&& value) {
        if (size_ == capacity_) {
            reserve(capacity_ ? capacity_ * 2 : 1);
        }
        alloc_.destroy(data_ + size_);
        alloc_.construct(data_ + size_++, std::move(value));
    }

    constexpr void pop_back() {
        --size_;
    }

    bool operator==(const my::vector<T, Allocator>& other) {
        if (std::tie(capacity_, size_) != std::tie(other.capacity_, other.size_)) {
            return false;
        }
        for (size_type i = 0; i < size_; ++i) {
            if (data_[i] != other.data_[i]) {
                return false;
            }
        }
        return true;
    }

   private:
    Allocator alloc_;
    T* data_ = nullptr;
    size_type capacity_ = 0;
    size_type size_ = 0;
};
}  // namespace my

template <typename T, class Allocator>
std::ostream& operator<<(std::ostream& os, const my::vector<T, Allocator>& v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        os << (it == v.begin() ? "" : " ") << *it;
    }

    return os;
}