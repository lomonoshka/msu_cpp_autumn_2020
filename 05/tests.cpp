#include "Serializer.cpp"
#include <sstream>
#include <cassert>

struct Data
{
  uint64_t a;
  bool b;
  uint64_t c;

  template <class Serializer>
  Error serialize(Serializer &serializer) const
  {
    return serializer(a, b, c);
  }

  template <class Deserializer>
  Error deserialize(Deserializer &deserializer)
  {
    return deserializer(a, b, c);
  }
};

void BasicTest() {
  Data x{1, true, 2};

  std::stringstream stream;

  Serializer serializer(stream);
  serializer.save(x);

  Data y{0, false, 0};

  Deserializer deserializer(stream);
  const Error err = deserializer.load(y);

  ASSERT(err == Error::NoError);

  ASSERT(x.a == y.a);
  ASSERT(x.b == y.b);
  ASSERT(x.c == y.c);

  std::stringstream stream_er;
  stream_er << "0 eror 1";

  Deserializer deserializer_er(stream_er);
  const Error err2 = deserializer.load(y);

  ASSERT(err2 == Error::CorruptedArchive);
}