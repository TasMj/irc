
#pragma once

#include <string>
#include <deque>
#include <stdexcept>
#include <iostream>
#include "Server.hpp"

typedef struct s_prefix {
    std::string nickname;
    bool        has_user;
    std::string user;
    bool        has_host;
    std::string host;
}   t_prefix;

typedef struct s_message {
    bool                    has_prefix;
    t_prefix                prefix;;
    std::string             command;
    std::deque<std::string> params;
    bool                    has_last_params;
    std::string             last_params;
}   t_message;

t_message       parse_message(std::string input);
std::ostream&   operator<<(std::ostream& os, t_message& msg);
