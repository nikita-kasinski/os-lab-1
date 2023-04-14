#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "employee.h"
#include "controller.h"

using namespace std;

int main(int argc, char *argv[])
{
    {
        string usage = "Expected 3 arguments. Usage : Reporter [binaryFileName]"
                       " [outputFileName] [paymentForHour]";
        if (argc != 4)
        {
            cerr << usage << "\n";
            return 1;
        }
    }
    string binFile(argv[1]);
    string reportfile(argv[2]);
    double paymentPerHour = atof(argv[3]);
    
    Controller::createReportFile(binFile, reportfile, paymentPerHour);
    return 0;
}