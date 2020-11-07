#pragma once
#include <stdint.h>
#include <iostream>

enum class Error
{
  NoError,
  CorruptedArchive
};

class Serializer
{
  std::ostream &out_;
  static constexpr char Separator = ' ';

public:
  explicit Serializer(std::ostream &out);

  template <class T>
  Error save(const T &);

  template <class... Args>
  Error operator()(const Args &...);

private:
  template <typename T>
  Error process(const T &);

  template <typename T, typename... Args>
  Error process(const T &, const Args &...);
};

template <>
Error Serializer::save<bool>(const bool &);

template <>
Error Serializer::save<uint64_t>(const uint64_t &);

class Deserializer
{
  std::istream &in_;
  static constexpr char Separator = ' ';

public:
  Deserializer(std::istream &in);

  template <class T>
  Error load(T &);

  template <class... Args>
  Error operator()(Args &...);

private:
  template <typename T>
  Error process(T &);

  template <typename T, typename... Args>
  Error process(T &, Args &...);
};

template <>
Error Deserializer::load<bool>(bool &);

template <>
Error Deserializer::load<uint64_t>(uint64_t &);
