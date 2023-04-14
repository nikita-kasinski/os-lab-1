#include <gtest/gtest.h>
#include <sstream>
#include <cstring>
#include <string>
#include "employee.h"
#include "controller.h"

TEST(TestSafeUnsignedIntegerInput, TestFailedInput)
{
    std::istringstream testStream("asdfbsda1\n2 sadgsadg123gasd\n 3\n");
    std::ostringstream ostream;
    size_t a, b;
    a = Controller::safeUnsignedIntegerInput(testStream, ostream, "", "");
    b = Controller::safeUnsignedIntegerInput(testStream, ostream, "", "");
    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 3);
}

TEST(TestSafeUnsignedIntegerInput, TestNegativeInput)
{
    std::istringstream testStream("skldghuhasdkjgn\n -1 \n2\n");
    std::ostringstream ostream;
    size_t a;
    a = Controller::safeUnsignedIntegerInput(testStream, ostream, "", "");
    EXPECT_EQ(a, 2);
}

TEST(TestSafePositiveDoubleInput, TestFailedInput)
{
    std::istringstream testStream("asdfbsda1\n2.3 sadgsadg123gasd\n 3.7\n");
    std::ostringstream ostream;
    constexpr double delta = 1e-9;
    double a, b;
    a = Controller::safePositiveDoubleInput(testStream, ostream, "", "");
    b = Controller::safePositiveDoubleInput(testStream, ostream, "", "");
    EXPECT_TRUE(std::abs(a - 2.3) < delta);
    EXPECT_TRUE(std::abs(b - 3.7) < delta);
}

TEST(TestSafePositiveDoubleInput, TestNegativeInput)
{
    std::istringstream testStream("skldghuhasdkjgn\n -1 \n2.7\n");
    std::ostringstream ostream;
    constexpr double delta = 1e-9;
    double a;
    a = Controller::safePositiveDoubleInput(testStream, ostream, "", "");
    EXPECT_TRUE(std::abs(a - 2.7) < delta);
}

TEST(TestPrintCreateBinaryFile, TestStandartFlow)
{
    size_t size = 3;
    std::string binFile = "binFile";
    Employee *employees = new Employee[size];
    std::ostringstream out;
    std::ostringstream expectedAnswer;
    std::string names[3] = {"vasya", "vitya", "kostya"};
    size_t hours[3] = {3, 5, 7};
    size_t nums[3] = {0, 1, 2};

    for (size_t i = 0; i < size; ++i)
    {
        expectedAnswer
            << std::setw(Controller::numWidth) << nums[i]
            << std::setw(Controller::nameWidth) << names[i]
            << std::setw(Controller::hoursWidth) << hours[i] << "\n";
    }

    employees[0].num = 0;
    strcpy(employees[0].name, "vasya");
    employees[0].hours = 3;

    employees[1].num = 1;
    strcpy(employees[1].name, "vitya");
    employees[1].hours = 5;

    employees[2].num = 2;
    strcpy(employees[2].name, "kostya");
    employees[2].hours = 7;

    EXPECT_TRUE(Controller::createBinaryFile(binFile, employees, size));
    EXPECT_TRUE(Controller::printBinaryFile(binFile, out));

    EXPECT_EQ(out.str(), expectedAnswer.str());
    delete[] employees;
}

TEST(TestPrintBinaryFile, TestNoFile)
{
    std::ostringstream out;
    EXPECT_FALSE(Controller::printBinaryFile("abacaba", out));
}

TEST(TestPrintCreateReportFile, TestStandartFlow)
{
    size_t size = 3;
    double payment = 5.6;
    std::string binFile = "binFile";
    std::string reportFile = "reportFile.txt";
    Employee *employees = new Employee[size];
    std::ostringstream out;
    std::ostringstream expectedAnswer;
    std::string names[3] = {"vasya", "vitya", "kostya"};
    size_t hours[3] = {3, 5, 7};
    size_t nums[3] = {0, 1, 2};

    expectedAnswer
        << std::setw(Controller::numWidth) << "id"
        << std::setw(Controller::nameWidth) << "name"
        << std::setw(Controller::hoursWidth) << "hours"
        << std::setw(Controller::paymentWidth) << "payment"
        << "\n";

    for (size_t i = 0; i < size; ++i)
    {
        expectedAnswer
            << std::setw(Controller::numWidth) << nums[i]
            << std::setw(Controller::nameWidth) << names[i]
            << std::setw(Controller::hoursWidth) << hours[i]
            << std::setw(Controller::paymentWidth) << hours[i] * payment << "\n";
    }

    employees[0].num = 0;
    strcpy(employees[0].name, "vasya");
    employees[0].hours = 3;

    employees[1].num = 1;
    strcpy(employees[1].name, "vitya");
    employees[1].hours = 5;

    employees[2].num = 2;
    strcpy(employees[2].name, "kostya");
    employees[2].hours = 7;

    EXPECT_TRUE(Controller::createBinaryFile(binFile, employees, size));
    EXPECT_TRUE(Controller::createReportFile(binFile, reportFile, payment));
    EXPECT_TRUE(Controller::printReportFile(reportFile, out));

    EXPECT_EQ(out.str(), expectedAnswer.str());
    delete[] employees;
}

TEST(TestPrintCreateFile, TestNoFile)
{
    EXPECT_FALSE(Controller::createReportFile("abacaba", "report.txt", 5));
}

TEST(TestPrintReportFile, TestNoFile)
{
    std::ostringstream out;
    EXPECT_FALSE(Controller::printReportFile("abacaba", out));
}