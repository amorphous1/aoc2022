#include <string>
#include <vector>

using namespace std;

vector<int> find_numbers(const string& str) {
    vector<int> numbers;
    char const* digits = "0123456789";
    size_t start, end = 0;
    do {
        start = str.find_first_of(digits, end);
        end = str.find_first_not_of(digits, start);
        numbers.push_back(stoi(str.substr(start, end != string::npos ? end-start : end)));
    } while (end != string::npos);
    return numbers;
}

bool contains(pair<int, int> a, pair<int, int> b) {
    return a.first <= b.first && b.first <= a.second && a.first <= b.second && b.second <= a.second;
}

bool overlaps(pair<int, int> a, pair<int, int> b) {
    return (a.first <= b.first && b.first <= a.second) || (a.first <= b.second && b.second <= a.second);
}

pair<int, int> day04(const vector<string>& lines) {
    int count_contains = 0, count_overlaps = 0;
    for (const string& line : lines) {
        vector<int> numbers = find_numbers(line);
        pair<int, int> a = make_pair(numbers[0], numbers[1]);
        pair<int, int> b = make_pair(numbers[2], numbers[3]);
        count_contains += contains(a, b) || contains(b, a) ? 1 : 0;
        count_overlaps += overlaps(a, b) || overlaps(b, a) ? 1 : 0;
    }
    return make_pair(count_contains, count_overlaps);
}