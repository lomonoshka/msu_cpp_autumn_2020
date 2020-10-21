#include "parser.h" 
#include <iostream>
void Parser::AddActionOnCondition(TCondition condition, TAction action) 
{
  actions_on_conditions_.push_back({condition, action});
}

void Parser::Apply() const {
  std::istringstream text_stream(text_);
  while (text_stream) {
    std::string token;
    text_stream >> token;
    if (!token.empty()) {
      for (const auto &[condition, action] : actions_on_conditions_) {
        if (condition(token)) {
          action(token);
        }
      }
    }
  }
}