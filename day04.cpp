#include <string>
#include <vector>
#include "common.h"

using namespace std;

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