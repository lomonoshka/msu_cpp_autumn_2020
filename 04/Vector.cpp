#pragma once

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
   public:
    Vector() = default;
    Vector(size_t size_);
    Vector(size_t size_, const T& value);
    Vector(const Vector& copied);
    Vector(Vector&& moved);
    Vector& operator=(const Vector& copied);
    Vector& operator=(Vector&& moved);
    ~Vector();

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    T* begin() { return data_; }
    T* end() { return data_ + size_; }
    const T* begin() const { return data_; }
    const T* end() const { return data_ + size_; }
    const T& back() const;
    
    T& back();
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();

    const T& operator[](size_t index) const;
    T& operator[](size_t index);

    bool empty() const { return size_ == 0; }
    void reserve(size_t capacity);
    void resize(size_t size);

   private:
    T* data_ = nullptr;
    size_t capacity_ = 0;
    size_t size_ = 0;
};

template <typename T>
Vector<T>::Vector(size_t size_)
    : data_(new T[size_]), capacity_(size_), size_(size_) {
    std::fill(begin(), end(), T());
}

template <typename T>
Vector<T>::Vector(size_t size_, const T& value)
    : data_(new T[size_]), capacity_(size_), size_(size_) {
    std::fill(begin(), end(), value);
}

template <typename T>
Vector<T>::Vector(const Vector& copied)
    : data_(new T[copied.capacity_]),
      capacity_(copied.capacity_),
      size_(copied.size_) {
    std::copy(copied.begin(), copied.end(), begin());
}

template <typename T>
Vector<T>::Vector(Vector&& moved)
    : data_(moved.data_), capacity_(moved.capacity_), size_(moved.size_) {
    moved.data_ = nullptr;
    moved.size_ = 0;
    moved.capacity_ = 0;
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data_;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& copied) {
    if (data_ != copied.data_) {
        if (capacity_ == copied.capacity_) {
            std::copy(copied.begin(), copied.end(), begin());
        } else {
            Vector<T> tmp(copied);
            std::swap(tmp.data_, data_);
            std::swap(tmp.capacity_, capacity_);
        }
        size_ = copied.size_;
    }

    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& moved) {
    if (data_ != moved.data_) {
        Vector<T> tmp(std::move(moved));
        std::swap(tmp.data_, data_);
        std::swap(tmp.size_, size_);
        std::swap(tmp.capacity_, capacity_);
    }

    return *this;
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("index out of range.");
    }

    return data_[index];
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= size_) {
        throw std::out_of_range("index out of range.");
    }

    return data_[index];
}

template <typename T>
void Vector<T>::reserve(size_t capacity) {
    if (capacity > capacity_) {
        auto new_data = new T[capacity];
        std::move(data_, data_ + capacity_, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = capacity;
    }
}

template <typename T>
void Vector<T>::resize(size_t size) {
    if (size < capacity_) {
        size_ = size;
    } else {
        auto new_data = new T[size];
        std::move(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
        std::fill(data_ + size_, data_ + size, T());
        capacity_ = size;
        size_ = size;
    }
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        auto capacityacity = capacity_ == 0 ? 1 : capacity_ * 2;
        reserve(capacityacity);
    }

    data_[size_] = value;
    size_++;
}

template <typename T>
void Vector<T>::push_back(T&& value) {
    if (size_ == capacity_) {
        auto capacityacity = capacity_ == 0 ? 1 : capacity_ * 2;
        reserve(capacityacity);
    }

    data_[size_] = value;
    size_++;
}

template <typename T>
const T& Vector<T>::back() const {
    if (empty()) {
        throw std::out_of_range("Vector is empty.");
    }

    return data_[size_ - 1];
}

template <typename T>
T& Vector<T>::back() {
    if (empty()) {
        throw std::out_of_range("Vector is empty.");
    }

    return data_[size_ - 1];
}

template <typename T>
void Vector<T>::pop_back() {
    if (!empty()) {
        size_--;
    }
}