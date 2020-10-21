#include "parser.h" 
#include <iostream>
void Parser::AddActionOnCondition(TCondition condition, TAction action) 
{
  actions_on_conditions_.push_back({condition, action});
}

void Parser::Apply() const {
  std::istringstream ss(text_);
  while (ss) {
    std::string token;
    ss >> token;
    for (const auto &[condition, action] : actions_on_conditions_) {
      if (condition(token)) {
        action(token);
      }
    }
  }
}