#include <gtest/gtest.h>
#include "day01.cpp"

using namespace std;

TEST(Samples, Day01) {
    vector<string> sample_input = {
            "1000", "2000", "3000",
            "",
            "4000",
            "",
            "5000", "6000",
            "",
            "7000", "8000", "9000",
            "",
            "10000",
    };
    EXPECT_EQ(day01a(sample_input), 24000);
    EXPECT_EQ(day01b(sample_input), 45000);
}


