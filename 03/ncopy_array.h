
#pragma ones

#include "array.h"
#include <iostream>
#include <functional>

template <typename T>
class ncopy_array{
public:
  ncopy_array(T *data_, const size_t &size);
  ncopy_array(const ncopy_array &other);

  ncopy_array& operator=(const ncopy_array &rhs);
  const T& operator[](const size_t &index) const;
  T& operator[](const size_t &index);

  array<T> apply(std::function<void(T &object)> func) const;
  ncopy_array& apply_inplace(std::function<void(T &object)> func);

  const T *begin() const;
  T *begin();

  const T *end() const;
  T *end();

  size_t size() const;

  array<T> operator+(const T &rhs) const;

  ncopy_array& operator+=(const T &rhs);

  array<T> operator-(const T &rhs) const;

  ncopy_array& operator-=(const T &rhs);

  array<T> operator*(const T &rhs) const;

  ncopy_array& operator*=(const T &rhs);

  array<T> operator/(const T &rhs) const;

  ncopy_array& operator/=(const T &rhs);
private:
  size_t size_ = 0;
  T *data_ = nullptr;
};

template <typename T>
ncopy_array<T>::ncopy_array(T *data, const size_t &size)
    : size_(size),
      data_(data)
{
}

template <typename T>
ncopy_array<T>::ncopy_array(const ncopy_array<T> &other)
    : size_(other.size_),
      data_(data_)
{
}

template <typename T>
ncopy_array<T>& ncopy_array<T>::operator=(const ncopy_array<T> &rhs)
{
  size_ = rhs.size_;
  data_ = rhs.data_;
  return *this;
}

template <typename T>
array<T> ncopy_array<T>::apply(std::function<void(T &object)> func) const
{
  array<T> result(data_, size_);
  for (auto &object : result)
  {
    func(object);
  }
  return result;
}

template <typename T>
ncopy_array<T>& ncopy_array<T>::apply_inplace(std::function<void(T &object)> func)
{
  for (auto &object : *this)
  {
    func(object);
  }
  return *this;
}

template <typename T>
array<T> ncopy_array<T>::operator+(const T &rhs) const
{
  return this->apply([&rhs](T &object) { object += rhs; });
}

template <typename T>
ncopy_array<T>& ncopy_array<T>::operator+=(const T &rhs)
{
  return this->apply_inplace([&rhs](T &object) { object += rhs; });
}

template <typename T>
array<T> ncopy_array<T>::operator-(const T &rhs) const
{
  return this->apply([rhs](T &object) { object -= rhs; });
}

template <typename T>
ncopy_array<T>& ncopy_array<T>::operator-=(const T &rhs)
{
  return this->apply_inplace([&rhs](T &object) { object -= rhs; });
}

template <typename T>
array<T> ncopy_array<T>::operator*(const T &rhs) const
{
  return this->apply([rhs](T &object) { object *= rhs; });
}

template <typename T>
ncopy_array<T>& ncopy_array<T>::operator*=(const T &rhs)
{
  return this->apply_inplace([&rhs](T &object) { object *= rhs; });
}

template <typename T>
array<T> ncopy_array<T>::operator/(const T &rhs) const
{
  return this->apply([rhs](T &object) { object /= rhs; });
}

template <typename T>
ncopy_array<T>& ncopy_array<T>::operator/=(const T &rhs)
{
  return this->apply_inplace([&rhs](T &object) { object /= rhs; });
}

template <typename T>
const T *ncopy_array<T>::begin() const
{
  return data_;
}

template <typename T>
T *ncopy_array<T>::begin()
{
  return data_;
}

template <typename T>
const T *ncopy_array<T>::end() const
{
  return data_ + size_;
}

template <typename T>
T *ncopy_array<T>::end()
{
  return data_ + size_;
}

template <typename T>
size_t ncopy_array<T>::size() const
{
  return size_;
}

template <typename T>
const T& ncopy_array<T>::operator[](const size_t &index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("Index out of range.");
  }
  else
  {
    return data_[index];
  }
}

template <typename T>
T& ncopy_array<T>::operator[](const size_t &index)
{
  if (index >= size_)
  {
    throw std::out_of_range("Index out of range.");
  }
  else
  {
    return data_[index];
  }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const ncopy_array<T> &arr) {
  os << "[";
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    os << *it << (it + 1 != arr.end() ? ", " : "");
  }
  os << "]";
  return os;
}