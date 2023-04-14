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