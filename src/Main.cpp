#include <iostream>
#include "windows.h"
#include "employee.h"
#include <fstream>
#include <stdio.h>

void Start(char* command)
{
    STARTUPINFO startupInfo;
    ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
    startupInfo.cb = sizeof(startupInfo);
    PROCESS_INFORMATION processInfo;
    ZeroMemory (&processInfo, sizeof(PROCESS_INFORMATION));
    if (!CreateProcess(NULL, command, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo))
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
    std::cout << "Enter binary file name\n";
    std::string binFile;
    std::cin >> binFile;
    binFile = "doc/" + binFile;
    std::cout << "Enter number of entries\n";
    int numberOfEntries;
    std::cin >> numberOfEntries; 
    char commandCreator[1000];
    sprintf(commandCreator, "%s %s %d", "Creator.exe", binFile.c_str(), numberOfEntries);
    Start(commandCreator);
    std::cout << "Binary file content:\n";
    std::ifstream fin(binFile, std::ios_base::binary);
    fin.read((char*)(&numberOfEntries), sizeof(int));
    for(int i = 0; i < numberOfEntries; ++i)
    {
        employee Employee;
        fin.read((char*)(&Employee), sizeof(employee));
        std::cout << Employee.num << " " << Employee.name << " " << Employee.hours << "\n";
    }
    std::cout << "\n";
    std::cout << "Enter report file name\n";
    std::string reportFile;
    std::cin >> reportFile;
    reportFile = "doc/" + reportFile;
    std::cout << "Enter payment per hour\n";
    double payment;
    std::cin >> payment;
    char commandReporter[1000];
    sprintf(commandReporter, "%s %s %s %lf", "Reporter.exe", binFile.c_str(), reportFile.c_str(), payment);
    Start(commandReporter);
    fin.close();
    std::string line;
    fin.open(reportFile);
    std::cout << "Report content:\n";
    while(getline(fin, line))
    {
        std::cout << line << "\n";
    }
    return 0;
}