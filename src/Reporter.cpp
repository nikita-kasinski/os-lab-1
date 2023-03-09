#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "employee.h"

using namespace std;

int main(int argc, char* argv[])
{
    string usage = "Expected 3 arguments. Usage : Reporter [binaryFileName]"
    " [outputFileName] [paymentForHour]";
    if (argc != 4)
    {
        cerr << usage << "\n";
        return 1;
    }
    string inFile(argv[1]);
    string outfile(argv[2]);
    double paymentPerHour = atof(argv[3]);
    int numberOfEntries;
    ifstream fin(inFile, ios_base::binary);
    fin.read((char*)(&numberOfEntries), sizeof(int));
    ofstream fout(outfile);
    fout << setw(5) << "id" << setw(12) << "name" << setw(10) << "hours" << setw(10) << "salary\n";
    for(int i = 0; i < numberOfEntries; ++i)
    {
        employee Employee;
        fin.read((char*)(&Employee), sizeof(employee));
        fout << setw(5) << Employee.num << setw(12) << Employee.name 
        << setw(10) << Employee.hours << setw(10) << Employee.hours * paymentPerHour << "\n";
    }
    fin.close();
    fout.close();
    return 0;
}