#pragma once

#include "ncopy_array.h"
using TShape = std::pair<size_t, size_t>;

template<typename T>
class matrix {
private:
  class iterator {
  public:
    iterator(size_t size, T *pointer);
    iterator(const iterator &other);

    bool operator!=(iterator const& other) const;
    bool operator==(iterator const& other) const;
    ncopy_array<T> operator*() const;
    iterator& operator++();

  private:
    size_t size_;
    T *pointer_;
};

public:
  matrix() = default;
  matrix(const TShape &shape);
  matrix(T *data_, const TShape &shape);
  matrix(const std::initializer_list<array<T>> &list);
  matrix(const matrix &other);
  ~matrix();

  matrix<T>& operator=(const matrix<T> &rhs);
  const ncopy_array<T> operator[](const size_t &index) const;
  ncopy_array<T> operator[](const size_t &index);
  
  const iterator begin() const;
  iterator begin();
  const iterator end() const;
  iterator end();
  
  size_t size() const;
  TShape shape() const;

  matrix apply(std::function<void(T &object)> func) const;
  matrix& apply_inplace(std::function<void(T &object)> func);

  template <typename U>
  matrix operator+(const U &rhs) const;

  template <typename U>
  matrix& operator+=(const U &rhs);

  template <typename U>
  matrix operator-(const U &rhs) const;

  template <typename U>
  matrix& operator-=(const U &rhs);

  template <typename U>
  matrix operator*(const U &rhs) const;

  template <typename U>
  matrix& operator*=(const U &rhs);

  template <typename U>
  matrix operator/(const U &rhs) const;

  template <typename U>
  matrix& operator/=(const U &rhs);

  bool operator==(const matrix& rhs) const;
  bool operator!=(const matrix& rhs) const;

protected:
  TShape shape_ = 0;
  T* data_ = nullptr;
};

//----------------------------------------------------------------------
//Implementation

template <typename T>
matrix<T>::iterator::iterator(size_t size, T *pointer)
    : size_(size),
      pointer_(pointer)
{
}

template <typename T>
matrix<T>::iterator::iterator(const iterator& other)
    : size_(other.size_),
      pointer_(other.pointer_)
{
}

template <typename T>
bool matrix<T>::iterator::operator!=(iterator const& other) const {
  return !(*this == other);
}

template <typename T>
bool matrix<T>::iterator::operator==(iterator const& other) const {
  return size_ == other.size_ && pointer_ == other.pointer_;
}

template <typename T>
ncopy_array<T> matrix<T>::iterator::operator*() const{
  return ncopy_array<T>(pointer_, size_);
}

template <typename T>
typename matrix<T>::iterator& matrix<T>::iterator::operator++() {
  pointer_ += size_;
  return *this;
}

template <typename T>
matrix<T>::matrix(const TShape &shape)
    : shape_(shape),
      data_(new T[size()])
{
}

template <typename T>
matrix<T>::matrix(T* data, const TShape &shape)
    : shape_(shape),
      data_(new T[size()])
{
  std::copy(data, data + size, data_);
}

template <typename T>
matrix<T>::matrix(const matrix<T> &other)
    : shape_(other.shape_),
      data_(new T[size()])
{
  std::copy(other.data_, other.data_ + other.size(), data_);
}

template <typename T>
matrix<T>::matrix(const std::initializer_list<array<T>> &list)
    : shape_(TShape({list.size(), list.begin()->size()})),
      data_(new T[size()])
{
  size_t i = 0;
  for (const array<T> &arr : list) {
    std::copy(arr.begin(), arr.end(), data_ + shape_.second * (i++));
  }
}

template <typename T>
matrix<T>::~matrix()
{
  delete[] data_;
}

template <typename T>
matrix<T>& matrix<T>::operator=(const matrix<T> &rhs)
{
  if (rhs.shape() == shape()) {
    std::copy(rhs.begin(), rhs.end(), data_);
  }
  else {
    array<T> tmp(rhs);
    std::swap(tmp.data_, data_);
    std::swap(tmp.shape_, shape_);
  }
  return *this;
}

template <typename T>
const ncopy_array<T> matrix<T>::operator[](const size_t &index) const
{
  if (index >= shape_.first)
  {
    throw std::out_of_range("Index out of range.");
  }
  else
  {
    return ncopy_array<T>(data_ + index * shape_.second, shape_.second);
  }
}

template <typename T>
ncopy_array<T> matrix<T>::operator[](const size_t &index)
{
  if (index >= shape_.first)
  {
    throw std::out_of_range("Index out of range.");
  }
  else
  {
    return ncopy_array<T>(data_ + index * shape_.second, shape_.second);
  }
}

template <typename T>
size_t matrix<T>::size() const {
  return shape_.first * shape_.second;
}

template <typename T>
TShape matrix<T>::shape() const {
  return shape_;
}

template <typename T>
const typename matrix<T>::iterator matrix<T>::begin() const {
  return iterator(shape_.second, data_);
}

template <typename T>
typename matrix<T>::iterator matrix<T>::begin() {
  return iterator(shape_.second, data_);
}

template <typename T>
const typename matrix<T>::iterator matrix<T>::end() const {
  return iterator(shape_.second, data_ + size());
}

template <typename T>
typename matrix<T>::iterator matrix<T>::end() {
  return iterator(shape_.second, data_ + size());
}

template <typename T>
matrix<T> matrix<T>::apply(std::function<void(T &object)> func) const
{
  matrix<T> result(*this);
  for (auto object : result)
  {
    object.apply_inplace(func);
  }
  return result;
}

template <typename T>
matrix<T>& matrix<T>::apply_inplace(std::function<void(T &object)> func)
{
  for (auto &object : *this)
  {
    object.apply(func);
  }
  return *this;
}

template <typename T>
template <typename U>
matrix<T> matrix<T>::operator+(const U &rhs) const
{
  return this->apply([&rhs](T &object) { object += rhs; });
}

template <typename T>
template <typename U>
matrix<T>& matrix<T>::operator+=(const U &rhs)
{
  return this->apply_inplace([&rhs](T &object) { object += rhs; });
}

template <typename T>
template <typename U>
matrix<T> matrix<T>::operator-(const U &rhs) const
{
  return this->apply([rhs](T &object) { object -= rhs; });
}

template <typename T>
template <typename U>
matrix<T>& matrix<T>::operator-=(const U &rhs)
{
  return this->apply_inplace([&rhs](T &object) { object -= rhs; });
}

template <typename T>
template <typename U>
matrix<T> matrix<T>::operator*(const U &rhs) const
{
  return this->apply([&rhs](T &object) { object *= rhs; });
}

template <typename T>
template <typename U>
matrix<T>& matrix<T>::operator*=(const U &rhs)
{
  return this->apply_inplace([&rhs](T &object) { object *= rhs; });
}

template <typename T>
template <typename U>
matrix<T> matrix<T>::operator/(const U &rhs) const
{
  return this->apply([rhs](T &object) { object /= rhs; });
}

template <typename T>
template <typename U>
matrix<T>& matrix<T>::operator/=(const U &rhs)
{
  return this->apply_inplace([&rhs](T &object) { object /= rhs; });
}

// Специализация шаблона для опреций над двумя матрицами
template <>
template <>
matrix<int> matrix<int>::operator+(const matrix<int> &rhs) const
{
  if(shape() != rhs.shape()) {
    throw std::logic_error("Matrixes with different shape.");
    return {{}};
  }
  matrix<int> result(shape()); 
  for (size_t i = 0; i < size(); ++i) {
    result.data_[i] = data_[i] + rhs.data_[i];
  }
  return result;
}

template<typename T>
bool matrix<T>::operator==(const matrix<T>& rhs) const {
  if(shape() != rhs.shape()) {
    return false;
  }
  matrix<int> result(shape()); 
  for (size_t i = 0; i < size(); ++i) {
    if(data_[i] != rhs.data_[i]) {
      return false;
    }
  }
  return true;
}

template<typename T>
bool matrix<T>::operator!=(const matrix<T>& rhs) const {
  return !(*this == rhs);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const matrix<T> &m) {
  os << "[";
  bool flag = false; 
  for (const auto &arr : m) {
    os << (flag ? ", \n " : "") << arr;
    flag = true;
  }
  os << "]";
  return os;
}