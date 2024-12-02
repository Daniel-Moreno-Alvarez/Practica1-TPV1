#pragma once

#include "GameError.h"

class FileNotFoundError : public GameError
{
public:
    FileNotFoundError(const std::string& message) : GameError(message) { m = message; }
};
