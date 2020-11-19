#pragma once

#include <stdexcept>
#include <string>

class InvalidArgs : public std::logic_error {
 public:
  InvalidArgs(const std::string& msg) : std::logic_error(msg) {}
};

class InvalidIndex : public std::logic_error {
 public:
  InvalidIndex(const std::string& msg) : std::logic_error(msg) {}
};

class UsageWithinContext : public std::logic_error {
 public:
  UsageWithinContext(const std::string& msg) : std::logic_error(msg) {}
};