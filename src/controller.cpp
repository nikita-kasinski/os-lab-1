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
    std::ifstream fin(binFile.c_str(), std::ios::binary);
    if (!fin.good())
    {
        return false;
    }
    size_t numberOfEntries;

    fin.read(reinterpret_cast<char *>(&numberOfEntries), sizeof(size_t));
    for (size_t i = 0; i < numberOfEntries; ++i)
    {
        Employee employee;
        fin.read(reinterpret_cast<char *>(&employee), sizeof(Employee));
        out
            << std::setw(Controller::numWidth) << employee.num
            << std::setw(Controller::nameWidth) << employee.name
            << std::setw(Controller::hoursWidth) << employee.hours << "\n";
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

bool Controller::createBinaryFile(const std::string &binFile, const Employee *employees, const size_t employeesSize)
{
    std::ofstream fout(binFile, std::ios::binary);
    if (!fout.good())
    {
        return false;
    }

    fout.write(reinterpret_cast<const char *>(&employeesSize), sizeof(size_t));
    for (size_t i = 0; i < employeesSize; ++i)
    {
        fout.write(reinterpret_cast<const char *>(&employees[i]), sizeof(Employee));
    }

    return true;
}

bool Controller::createReportFile(
    const std::string &binFile,
    const std::string &reportFile,
    const double payment)
{
    std::ifstream fin(binFile.c_str(), std::ios::binary);
    std::ofstream fout(reportFile.c_str());

    if (!fin.good())
    {
        return false;
    }

    size_t numberOfEntries;
    fin.read(reinterpret_cast<char *>(&numberOfEntries), sizeof(size_t));

    // print headers
    fout
        << std::setw(Controller::numWidth) << "id" 
        << std::setw(Controller::nameWidth) << "name" 
        << std::setw(Controller::hoursWidth) << "hours" 
        << std::setw(Controller::paymentWidth) << "payment" << "\n";

    for (size_t i = 0; i < numberOfEntries; ++i)
    {
        Employee employee;
        fin.read(reinterpret_cast<char *>(&employee), sizeof(Employee));
        fout 
        << std::setw(Controller::numWidth) << employee.num 
        << std::setw(Controller::nameWidth)<< employee.name 
        << std::setw(Controller::hoursWidth) << employee.hours 
        << std::setw(Controller::paymentWidth) << employee.hours * payment << "\n";
    }

    return true;
}