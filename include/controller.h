#pragma once
#include <string>
#include <fstream>
#include "employee.h"

class Controller
{
public:
    constexpr static size_t numWidth = 5;
    constexpr static size_t nameWidth = 12;
    constexpr static size_t hoursWidth = 10;
    constexpr static size_t paymentWidth = 10;

    static size_t safeUnsignedIntegerInput(
        std::istream &in,
        std::ostream &out,
        const std::string &inputPrompt,
        const std::string &inputFailedPrompt);

    static double safePositiveDoubleInput(
        std::istream &in,
        std::ostream &out,
        const std::string &inputPrompt,
        const std::string &inputFailedPrompt);

    static bool printBinaryFile(const std::string &binFile, std::ostream &out);

    static bool printReportFile(const std::string &reportFile, std::ostream &out);

    static bool createBinaryFile(const std::string &binFile, const Employee *employees, const size_t employeesSize);

    static bool createReportFile(
        const std::string &binFile,
        const std::string &reportFile,
        const double payment);
};