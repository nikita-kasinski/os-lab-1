#include <limits>
#include "controller.h"

size_t Controller::safeUnsignedIntegerInput(
    std::istream &in, 
    std::ostream &out, 
    const std::string &inputPrompt, 
    const std::string &inputFailedPrompt)
{
    constexpr auto maxStreamSize = std::numeric_limits<std::streamsize>::max();
    int tempAns = -1;
    bool failed = false;

    while (tempAns <= 0)
    {
        if (failed)
        {
            out << inputFailedPrompt;
        }
        else
        {
            failed = true;
        }
        out << inputPrompt;
        in >> tempAns;
        if (!in.good())
        {
            in.clear();
            in.ignore(maxStreamSize, '\n');
            tempAns = -1;
        }
    }
    return static_cast<size_t>(tempAns);
}