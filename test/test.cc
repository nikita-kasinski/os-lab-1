#include <gtest/gtest.h>
#include <sstream>
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