#include "tests.h"
#include "test_runner.h"
#include <iostream>


std::string CreateRandomText(int tokensize, int textsize) {
  std::ostringstream text_stream;
  for (int i = 0; i < textsize; ++i) {
  std::string token = "";
  int token_size = rand() % (tokensize - 1) + 1;
  for (int j = 0; j < token_size; ++j) {
    char tmp;
    if(rand() % 2) {
      tmp = static_cast<char>(rand() % 9) + 48;
    } else {
      tmp = static_cast<char>(rand() % 57) + 65;
    }
    token += tmp;
  }
  text_stream << token << " ";
  }
  return std::move(text_stream.str());
}

bool IsInteger(const std::string &s) {
  return !s.empty() && std::find_if(s.begin(), s.end(), [](char c){return !std::isdigit(c);}) == s.end();
}

void TestIsInteger() {
  ASSERT(!IsInteger("asdas"));
  ASSERT(!IsInteger("asd45"));
  ASSERT(!IsInteger("45asdas"));
  ASSERT(IsInteger("451"));
  ASSERT(IsInteger("051"));
  ASSERT(!IsInteger("1OOO0")); //tricky
}

void TestParser() {
  auto IsNotInteger = [](const std::string &s) {return !IsInteger(s);};

  //To understand that code work correctly we will create two vectors for each condition. We will push_back
  //token to respective vectors when relevant condition is true.
  std::vector<std::string> integers, not_integers;
  auto push_integer = [&integers](const std::string &s) {integers.push_back(std::move(s));};
  auto push_notinteger = [&not_integers](const std::string &s) {not_integers.push_back(std::move(s));};
  
  std::string text = CreateRandomText(8, 1000);
  Parser parser(text);
  parser.AddActionOnCondition(IsInteger, push_integer);
  parser.AddActionOnCondition(IsNotInteger, push_notinteger);
  parser.Apply();

  //Create two vectors to compare results
  std::vector<std::string> integers_true, not_integers_true;
  std::istringstream text_stream(text);
  while (text_stream) {
    std::string token;
    text_stream >> token;
    if (!token.empty()) {
      if (IsInteger(token)) {
        integers_true.push_back(std::move(token));
      } else {
        not_integers_true.push_back(std::move(token));
      }
    }
  }

  ASSERT(integers == integers_true);
  ASSERT(not_integers == not_integers_true);
}