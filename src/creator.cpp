#include <iostream>
#include <fstream>
#include <string>
#include "employee.h"
#include "controller.h"

using namespace std;

int main(int argc, char *argv[])
{
    {
        string usage = "Usage: Creator [filename] [number of entries]";
        if (argc != 3)
        {
            cerr << usage << "\n";
            return 1;
        }
    }

    string binFile = string(argv[1]);
    size_t numberOfEntries = static_cast<size_t>(atoi(argv[2]));
    Employee *employees = new Employee[numberOfEntries];
    string message = "Enter entries in the form: [id] [employeeName] [hours worked]";

    cout << message << "\n";
    for (size_t i = 0; i < numberOfEntries; ++i)
    {
        cin >> employees[i].num >> employees[i].name >> employees[i].hours;
    }
    
    Controller::createBinaryFile(binFile, employees, numberOfEntries);

    delete[] employees;
    return 0;
}