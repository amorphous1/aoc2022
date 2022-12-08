#include <gtest/gtest.h>
#include "day01.cpp"
#include "day02.cpp"
#include "day03.cpp"
#include "day04.cpp"
#include "day05.cpp"
#include "day06.cpp"
#include "day07.cpp"
#include "day08.cpp"

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

TEST(Samples, Day05a) {
    stack<char> s1({'Z', 'N'}), s2({'M', 'C', 'D'}), s3({'P'});
    vector<stack<char>> sample_stacks = { s1, s2, s3 };
    vector<string> sample_moves = {
            "move 1 from 2 to 1",
            "move 3 from 1 to 3",
            "move 2 from 2 to 1",
            "move 1 from 1 to 2",
    };
    EXPECT_EQ(day05a(sample_stacks, sample_moves), "CMZ");
}

TEST(Samples, Day05b) {
    stack<char> s1({'Z', 'N'}), s2({'M', 'C', 'D'}), s3({'P'});
    vector<stack<char>> sample_stacks = { s1, s2, s3 };
    vector<string> sample_moves = {
            "move 1 from 2 to 1",
            "move 3 from 1 to 3",
            "move 2 from 2 to 1",
            "move 1 from 1 to 2",
    };
    EXPECT_EQ(day05b(sample_stacks, sample_moves), "MCD");
}

TEST(Samples, Day06) {
    EXPECT_EQ(day06a("mjqjpqmgbljsphdztnvjfqwrcgsmlb"), 7);
    EXPECT_EQ(day06a("bvwbjplbgvbhsrlpgdmjqwftvncz"), 5);
    EXPECT_EQ(day06a("nppdvjthqldpwncqszvftbrmjlhg"), 6);
    EXPECT_EQ(day06a("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg"), 10);
    EXPECT_EQ(day06a("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"), 11);

    EXPECT_EQ(day06b("mjqjpqmgbljsphdztnvjfqwrcgsmlb"), 19);
    EXPECT_EQ(day06b("bvwbjplbgvbhsrlpgdmjqwftvncz"), 23);
    EXPECT_EQ(day06b("nppdvjthqldpwncqszvftbrmjlhg"), 23);
    EXPECT_EQ(day06b("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg"), 29);
    EXPECT_EQ(day06b("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"), 26);
}

TEST(Samples, Day07) {
    vector<string> sample_input = {
            "$ cd /",
            "$ ls",
            "dir a",
            "14848514 b.txt",
            "8504156 c.dat",
            "dir d",
            "$ cd a",
            "$ ls",
            "dir e",
            "29116 f",
            "2557 g",
            "62596 h.lst",
            "$ cd e",
            "$ ls",
            "584 i",
            "$ cd ..",
            "$ cd ..",
            "$ cd d",
            "$ ls",
            "4060174 j",
            "8033020 d.log",
            "5626152 d.ext",
            "7214296 k",
    };
    EXPECT_EQ(day07a(sample_input), 95437);
    EXPECT_EQ(day07b(sample_input), 24933642);
}

TEST(Samples, Day08) {
    vector<string> sample_input = {
            "30373",
            "25512",
            "65332",
            "33549",
            "35390",
    };
    EXPECT_EQ(day08a(sample_input), 21);
    EXPECT_EQ(day08b(sample_input), 8);
}
