#pragma once

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "format_exceptions.h"

template <class T>
std::string get_parametrs(const T &param) {
    std::stringstream s;
    s << param;
    return s.str();
}

template <class... Args>
std::string format(const std::string &s, const Args &... args) {
    std::vector<std::string> param = {get_parametrs(args)...};
    std::stringstream str_format;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '}') {
            throw UsageWithinContext("Incorrect positioning of brackets");
        } else if (s[i] == '{') {
            int tmp_num = 0;
            for (++i; s[i] != '}' && i < s.size(); ++i) {
                if (!std::isdigit(s[i])) {
                    throw InvalidArgs("Incorrect data in argument");
                }
                tmp_num *= 10;
                tmp_num += s[i] - '0';
            }
            if (s[i] != '}') {
                throw UsageWithinContext("Incorrect positioning of brackets");
            }
            if (tmp_num >= param.size())
                throw InvalidIndex("Index out of range");
            str_format << param[tmp_num];
        } else {
            str_format << s[i];
        }
    }

    return str_format.str();
}