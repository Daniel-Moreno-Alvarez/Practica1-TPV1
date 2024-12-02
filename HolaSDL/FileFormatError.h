#pragma once

#include "GameError.h"

class FileFormatError : public GameError
{
public:
    FileFormatError(const std::string& message) : GameError(message) { m = message; }
};