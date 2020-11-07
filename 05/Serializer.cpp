#include "Serializer.h"

Serializer::Serializer(std::ostream &out)
    : out_(out)
{
}

template <class T>
Error Serializer::save(const T &object)
{
  return object.serialize(*this);
}

template <class... Args>
Error Serializer::operator()(const Args &... args)
{
  return process(args...);
}

template <typename T>
Error Serializer::process(const T &obj)
{
  return save(obj);
}

template <typename T, typename... Args>
Error Serializer::process(const T &obj, const Args &... args)
{
  if (save(obj) == Error::NoError)
    return process(args...);
  else
    return Error::CorruptedArchive;
}

template <>
Error Serializer::save<bool>(const bool &object)
{
  if (object)
  {
    out_ << "true" << Separator;
  }
  else
  {
    out_ << "false" << Separator;
  }

  if (out_.fail())
    return Error::CorruptedArchive;

  return Error::NoError;
}

template <>
Error Serializer::save(const uint64_t &object)
{
  out_ << object << Separator;

  if (out_.fail())
    return Error::CorruptedArchive;

  return Error::NoError;
}

Deserializer::Deserializer(std::istream &in)
    : in_(in)
{
}

template <class T>
Error Deserializer::load(T &object)
{
  return object.deserialize(*this);
}

template <class... Args>
Error Deserializer::operator()(Args &... args)
{
  return process(args...);
}

template <typename T>
Error Deserializer::process(T &obj)
{
  return load(obj);
}

template <typename T, typename... Args>
Error Deserializer::process(T &obj, Args &... args)
{
  if (load(obj) == Error::NoError)
    return process(args...);
  else
    return Error::CorruptedArchive;
}

template <>
Error Deserializer::load<bool>(bool &object)
{
  std::string tmp;
  in_ >> tmp;
  if (tmp == "true")
  {
    object = true;
  }
  else if (tmp == "false")
  {
    object = false;
  }
  else
    return Error::CorruptedArchive;

  return Error::NoError;
}

template <>
Error Deserializer::load(uint64_t &object)
{
  in_ >> object;

  if (in_.fail())
    return Error::CorruptedArchive;

  return Error::NoError;
}
