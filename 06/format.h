#pragma once

#include <vector>
#include <sstream>
#include <string>
#include <cctype>
#include "format_exceptions.h"

template <class T>
std::string get_parametrs(T &&param)
{
    std::stringstream s;
    s << param;
    return s.str();
}

template <class... Args>
std::string format(const std::string &s, Args &&... args)
{
    std::vector<std::string> param = {get_parametrs(args)...};
    std::stringstream str_format;
    for (size_t i = 0; i < s.size(); ++i)
    {

        if (s[i] == '}')
        {
            throw UsageWithinContext("Brackets can not use within context");
        }
        else if (s[i] == '{')
        {
            int tmp_num = 0;
            i++;
            for (i; s[i] != '}'; ++i)
            {
                if (s[i] > '9' || s[i] < '0')
                {
                    throw InvalidArgs("Incorrect data in arguments");
                }

                tmp_num *= 10;
                tmp_num += s[i] - '0';
            }
            if (tmp_num >= param.size())
                throw InvalidIndex("Index out of range");
            str_format << param[tmp_num];
        }
        else
            str_format << s[i];
    }

    return str_format.str();
}
