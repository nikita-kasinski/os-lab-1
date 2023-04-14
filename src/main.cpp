#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include "employee.h"
#include "controller.h"

void Start(char *command)
{
    STARTUPINFOA startupInfo;
    ZeroMemory(&startupInfo, sizeof(STARTUPINFOA));
    startupInfo.cb = sizeof(startupInfo);
    PROCESS_INFORMATION processInfo;
    ZeroMemory(&processInfo, sizeof(PROCESS_INFORMATION));
    if (!CreateProcessA(NULL, command, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo))
    {
        std::cout << "Something went wrong\n";
        system("pause");
    }

    WaitForSingleObject(processInfo.hProcess, INFINITE);
    CloseHandle(processInfo.hThread);
    CloseHandle(processInfo.hProcess);
}
int main()
{
    std::string binFile;
    std::string reportFile;
    size_t numberOfEntries;
    double payment;

    std::cout << "Enter binary file name\n";
    std::cin >> binFile;

    numberOfEntries = Controller::safeUnsignedIntegerInput(
        std::cin, 
        std::cout, 
        "Enter number of entries\n", 
        "Value must be positive integer\n");

    {
        std::string creator = "Creator.exe";
        std::string commandCreator = creator + " " + binFile + " " + std::to_string(numberOfEntries);
        Start(const_cast<char *>(commandCreator.c_str()));
    }

    std::cout << "Binary file content:\n";
    Controller::printBinaryFile(binFile, std::cout);
    
    std::cout << "Enter report file name\n";
    std::cin >> reportFile;

    payment = Controller::safePositiveDoubleInput(
        std::cin, 
        std::cout, 
        "Enter payment per hour\n", 
        "Value must be positive double\n");

    {
        std::string reporter = "Reporter.exe";
        std::string commandReporter = reporter + " " + binFile + " " + reportFile + " " + std::to_string(payment);
        Start(const_cast<char *>(commandReporter.c_str()));
    }

    std::cout << "Report content:\n";
    Controller::printReportFile(reportFile, std::cout);

    return 0;
}