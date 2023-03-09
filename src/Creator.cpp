#include <iostream>
#include <fstream>
#include <string>
#include "employee.h"

using namespace std;

int main(int argc, char *argv[])
{
    string usage = "Usage: Creator [filename] [number of entries]";
    if (argc != 3)
    {
        cerr << usage << "\n"; 
        return 1;
    }
    string fileName = string(argv[1]);
    int numberOfEntries = atoi(argv[2]);
    string message = "Enter entries in the form: [id] [employeeName] [hours worked]";
    cout << message << "\n";
    ofstream fout(fileName, std::ios_base::binary);
    employee *employees = new employee[numberOfEntries];
    fout.write((char*)(&numberOfEntries), sizeof(int));
    for (int i = 0; i < numberOfEntries; ++i)
    {
        cin >> employees[i].num >> employees[i].name >> employees[i].hours;
        fout.write((char*)(&employees[i]), sizeof(employee));
    }
    fout.close();
    delete[] employees;
    return 0;
}