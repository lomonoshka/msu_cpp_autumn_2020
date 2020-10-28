#pragma ones

#include <iostream>
#include <functional>

using TShape = std::pair<size_t, size_t>;

template <typename T>
class array
{
public:
  array() = default;
  array(const size_t &size);
  array(T *data_, const size_t &size);
  array(const std::initializer_list<T> &list);
  array(const array &other);
  ~array();

  array<T> &operator=(const array<T> &rhs);
  const T &operator[](const size_t &index) const;
  T &operator[](const size_t &index);

  const T *begin() const;
  T *begin();

  const T *end() const;
  T *end();

  size_t size() const;

  array apply(std::function<void(T &object)> func) const;

  template <typename U>
  array operator+(const U &rhs) const;

  template <typename U>
  array &operator+=(const U &rhs);

  template <typename U>
  array operator-(const U &rhs) const;

  template <typename U>
  array &operator-=(const U &rhs);

  template <typename U>
  array operator*(const U &rhs) const;

  template <typename U>
  array &operator*=(const U &rhs);

  template <typename U>
  array operator/(const U &rhs) const;

  template <typename U>
  array &operator/=(const U &rhs);

private:
  size_t size_ = 0;
  T *data_ = nullptr;
};

//----------------------------------------------------------------------
//Implementation

template <typename T>
array<T>::array(const size_t &size)
    : size_(size),
      data_(new T[size_])
{
}

template <typename T>
array<T>::array(T *data, const size_t &size)
    : size_(size),
      data_(new T[size_])
{
  std::copy(data, data + size, data_);
}

template <typename T>
array<T>::array(const array<T> &other)
    : size_(other.size_),
      data_(new T[size_])
{
  std::copy(other.begin(), other.end(), data_);
}

template <typename T>
array<T>::array(const std::initializer_list<T> &list)
: size_(list.size()),
  data_(new T[size_])
{
  std::copy(list.begin(), list.end(), data_);
}

template <typename T>
array<T>::~array() {
  delete[] data_;
  size_ = 0;
}

template <typename T>
array<T>& array<T>::operator=(const array<T> &rhs) {
  if (rhs.size_ <= size_) {
    std::copy(rhs.begin(), rhs.end(), data_);
  } else {
    array<T> tmp(rhs);
    std::swap(tmp.data_, data_);
    std::swap(tmp.size_, size_);
  }
  return *this;
}

template <typename T>
const T &array<T>::operator[](const size_t &index) const
{
  if (index >= size_) {
    throw std::out_of_range("Index out of range.");
  } else {
    return data_[index];
  }
}

template <typename T>
T &array<T>::operator[](const size_t &index)
{
  if (index >= size_) {
    throw std::out_of_range("Index out of range.");
  } else {
    return data_[index];
  }
}

template <typename T>
size_t array<T>::size() const {
  return size_;
}

template <typename T>
array<T> array<T>::apply(std::function<void(T &object)> func) const
{
  array<T> result(*this);
  for (auto &object : result) {
    func(object);
  }
  return result; 
}

template <typename T>
template <typename U>
array<T> array<T>::operator+(const U &rhs) const
{
  return this->apply([&rhs](T &object) { object += rhs; });
}

template <typename T>
template <typename U>
array<T> &array<T>::operator+=(const U &rhs)
{
  *this = *this + rhs;
  return *this;
}

template <typename T>
template <typename U>
array<T> array<T>::operator-(const U &rhs) const
{
  return this->apply([rhs](T &object) { object -= rhs; });
}

template <typename T>
template <typename U>
array<T> &array<T>::operator-=(const U &rhs)
{
  *this = *this - rhs;
  return *this;
}

template <typename T>
template <typename U>
array<T> array<T>::operator*(const U &rhs) const
{
  return this->apply([rhs](T &object) { object *= rhs; });
}

template <typename T>
template <typename U>
array<T> &array<T>::operator*=(const U &rhs)
{
  *this = *this * rhs;
  return *this;
}

template <typename T>
template <typename U>
array<T> array<T>::operator/(const U &rhs) const
{
  return this->apply([rhs](T &object) { object /= rhs; });
}

template <typename T>
template <typename U>
array<T> &array<T>::operator/=(const U &rhs)
{
  *this = *this / rhs;
  return *this;
}

template <typename T>
const T *array<T>::begin() const
{
  return data_;
}

template <typename T>
T *array<T>::begin()
{
  return data_;
}

template <typename T>
const T *array<T>::end() const
{
  return data_ + size_;
}

template <typename T>
T *array<T>::end()
{
  return data_ + size_;
}

// template<typename T>
// class matrix
// {
// public:

//     matrix(TShape shape);
//     matrix(const matrix &other);
//     ~matrix();

//     const array operator[](const size_t&) const;
//     array operator[](const size_t&);

//     template<typename t_multy>
//     matrix& operator*(const tmulty &rhs) const;

//     template<typename t_multy>
//     matrix& operator*=(const tmulty &rhs);

//     bool operator==(const matrix &rhs) const;
//     bool operator!=(const matrix &rhs) const;

//     TShape shape() const;
// private:
//     TShape shape_;
//     T* data_;
// };
