#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include "employee.h"

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
    int numberOfEntries;

    std::cout << "Enter binary file name\n";
    std::cin >> binFile;

    std::cout << "Enter number of entries\n";
    std::cin >> numberOfEntries;

    {
        std::string creator = "Creator.exe";
        std::string commandCreator = creator + " " + binFile + " " + std::to_string(numberOfEntries);
        Start(const_cast<char *>(commandCreator.c_str()));
    }

    std::cout << "Binary file content:\n";
    std::ifstream fin(binFile, std::ios_base::binary);
    fin.read((char *)(&numberOfEntries), sizeof(int));
    for (int i = 0; i < numberOfEntries; ++i)
    {
        employee Employee;
        fin.read((char *)(&Employee), sizeof(employee));
        std::cout << Employee.num << " " << Employee.name << " " << Employee.hours << "\n";
    }
    fin.close();
    std::cout << "\n";

    std::string reportFile;

    std::cout << "Enter report file name\n";
    std::cin >> reportFile;

    double payment;

    std::cout << "Enter payment per hour\n";
    std::cin >> payment;

    {
        std::string reporter = "Reporter.exe";
        std::string commandReporter = reporter + " " + binFile + " " + reportFile + " " + std::to_string(payment);
        Start(const_cast<char *>(commandReporter.c_str()));
    }

    std::string line;
    fin.open(reportFile);
    std::cout << "Report content:\n";
    while (getline(fin, line))
    {
        std::cout << line << "\n";
    }
    return 0;
}