#include <vector>
#include <map>

using namespace std;

int day02(const vector<string>& lines, map<string, int> strategy_to_score) {
    int total_score = 0;
    for (const string& line : lines) {
        total_score += strategy_to_score.at(line);
    }
    return total_score;
}

int day02a(const vector<string>& lines) {
    const map<string, int> strategy_to_score = {
            {"A X", 1 + 3}, {"B Y", 2 + 3}, {"C Z", 3 + 3},
            {"A Y", 2 + 6}, {"B Z", 3 + 6}, {"C X", 1 + 6},
            {"A Z", 3 + 0}, {"B X", 1 + 0}, {"C Y", 2 + 0},
    };
    return day02(lines, strategy_to_score);
}

int day02b(const vector<string>& lines) {
    const map<string, int> strategy_to_score = {
            {"A X", 3 + 0}, {"B Y", 2 + 3}, {"C Z", 1 + 6},
            {"A Y", 1 + 3}, {"B Z", 3 + 6}, {"C X", 2 + 0},
            {"A Z", 2 + 6}, {"B X", 1 + 0}, {"C Y", 3 + 3},
    };
    return day02(lines, strategy_to_score);
}