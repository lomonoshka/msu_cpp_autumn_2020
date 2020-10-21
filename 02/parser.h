#pragma once

#include <vector>
#include <map>
#include <functional>
#include <sstream>

using TCondition = std::function<bool(const std::string&)>;
using TAction = std::function<void(const std::string&)>;

class Parser {
public:
  explicit Parser(const std::string &text) : actions_on_conditions_(), text_(text) {};
  void AddActionOnCondition(TCondition condition, TAction action);
  void Apply() const;
private:
  std::vector<std::pair<TCondition, TAction>> actions_on_conditions_;
  std::string text_;
};