#pragma once
#include <string>

#include <stdexcept>

class GameError : public std::logic_error
{
protected:
    std::string m;

public:

    GameError(const std::string& message) : logic_error(message) {
        m = message;
    }

    char const* what() const { return m.c_str(); }
};
