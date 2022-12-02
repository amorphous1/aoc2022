#include <algorithm>
#include <vector>

using namespace std;

int day01a(const vector<string>& lines) {
    int max_calories, current_calories = 0;
    for (const string& line : lines) {
        if (line.empty()) {
            max_calories = max(max_calories, current_calories);
            current_calories = 0;
        } else {
            current_calories += stoi(line);
        }
    }
    return max(max_calories, current_calories);
}

int day01b(const vector<string>& lines) {
    vector<int> calories;
    int current_calories = 0;
    for (const string& line : lines) {
        if (line.empty()) {
            calories.push_back(current_calories);
            current_calories = 0;
        } else {
            current_calories += stoi(line);
        }
    }
    calories.push_back(current_calories);
    sort(calories.rbegin(), calories.rend());

    return calories[0] + calories[1] + calories[2];
}
