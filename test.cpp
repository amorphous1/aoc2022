#include <gtest/gtest.h>
#include "day01.cpp"
#include "day02.cpp"
#include "day03.cpp"
#include "day04.cpp"

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

TEST(Samples, Day02) {
    vector<string> sample_input = {
            "A Y",
            "B X",
            "C Z",
    };
    EXPECT_EQ(day02a(sample_input), 15);
    EXPECT_EQ(day02b(sample_input), 12);
}

TEST(Samples, Day03) {
    vector<string> sample_input = {
            "vJrwpWtwJgWrhcsFMMfFFhFp",
            "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
            "PmmdzqPrVvPwwTWBwg",
            "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
            "ttgJtRGJQctTZtZT",
            "CrZsJsPPZsGzwwsLwLmpwMDw",
    };
    EXPECT_EQ(day03a(sample_input), 157);
    EXPECT_EQ(day03b(sample_input), 70);
}

TEST(Samples, Day04) {
    vector<string> sample_input = {
            "2-4,6-8",
            "2-3,4-5",
            "5-7,7-9",
            "2-8,3-7",
            "6-6,4-6",
            "2-6,4-8",
    };
    EXPECT_EQ(day04(sample_input), make_pair(2, 4));
}

