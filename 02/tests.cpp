#include "tests.h"
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
      tmp = static_cast<char>(rand() % 26) + 65;
    }
    token += tmp;
  }
  text_stream << " " << token;
  }
  return std::move(text_stream.str());
}

void TestWithFunctionsFromHw() {
  //Conditions if token is integer or not
  auto is_integer = [](const std::string &s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c){return !std::isdigit(c);}) == s.end();
  };
  auto isnot_integer = [is_integer](const std::string &s) {return !is_integer(s);};

  //To understand that code is correct we will create two vectors and push_back
  //to them strings that are required condition
  std::vector<std::string> integers, not_integers;
  auto push_integer = [&integers](const std::string &s) {integers.push_back(std::move(s));};
  auto push_notinteger = [&not_integers](const std::string &s) {not_integers.push_back(std::move(s));};
  
  std::string text = CreateRandomText(8, 1000);
  Parser parser(text);
  parser.AddActionOnCondition(is_integer, push_integer);
  parser.AddActionOnCondition(isnot_integer, push_notinteger);
  parser.Apply();

  //Create to vectors to compare results
  std::vector<std::string> integers_true, not_integers_true;
  std::istringstream text_stream(text);
  while (text_stream) {
    std::string token;
    text_stream >> token;
    if(is_integer(token)) {
      integers_true.push_back(token);
    } else {
      not_integers_true.push_back(token);
    }
  }

  assert(integers == integers_true);
  assert(not_integers == not_integers_true);
}