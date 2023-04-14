#include <limits>
#include <iomanip>
#include "controller.h"
#include "employee.h"

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

double Controller::safePositiveDoubleInput(
    std::istream &in,
    std::ostream &out,
    const std::string &inputPrompt,
    const std::string &inputFailedPrompt)
{
    constexpr auto maxStreamSize = std::numeric_limits<std::streamsize>::max();
    double tempAns = -1;
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
    return tempAns;
}

bool Controller::printBinaryFile(const std::string &binFile, std::ostream &out)
{
    std::ifstream fin(binFile.c_str());
    if (!fin.good())
    {
        return false;
    }
    size_t numberOfEntries;

    fin.read((char *)(&numberOfEntries), sizeof(size_t));
    for (int i = 0; i < numberOfEntries; ++i)
    {
        Employee employee;
        fin.read((char *)(&employee), sizeof(Employee));
        out
            << Controller::numWidth << employee.num
            << Controller::nameWidth << employee.name
            << Controller::hoursWidth << employee.hours << "\n";
    }

    return true;
}

bool Controller::printReportFile(const std::string &reportFile, std::ostream &out)
{
    std::ifstream fin(reportFile.c_str());
    if (!fin.good())
    {
        return false;
    }

    std::string line;
    while (getline(fin, line))
    {
        out << line << "\n";
    }

    return true;
}