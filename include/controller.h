#pragma once
#include <string>
#include <fstream>

class Controller
{
public:
    static size_t safeUnsignedIntegerInput(
        std::istream &in, 
        std::ostream &out, 
        const std::string &inputPrompt, 
        const std::string &inputFailedPrompt);
};