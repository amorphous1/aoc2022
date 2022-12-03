#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int day03a(const vector<string>& lines) {
    int result = 0;
    for (const string& line : lines) {
        string compartment1 = line.substr(0, line.length() / 2);
        string compartment2 = line.substr(line.length() / 2);
        set<char> compartment1items(compartment1.begin(), compartment1.end());
        set<char> compartment2items(compartment2.begin(), compartment2.end());
        set<char> common_items;
        set_intersection(compartment1items.begin(), compartment1items.end(),
                         compartment2items.begin(), compartment2items.end(),
                         inserter(common_items, common_items.begin()));
        for (char common_char : common_items) {
            int priority = common_char >= 'a' ? common_char - 'a' + 1 : common_char - 'A' + 27;
            result += priority;
        }
    }
    return result;
}

int day03b(const vector<string>& lines) {
    int result = 0;
    set<char> common_items1, common_items2;
    for (int i = 0; i < lines.size(); i++) {
        if (i % 3 == 1) {
            set<char> prev_items(lines[i-1].begin(), lines[i-1].end());
            set<char> curr_items(lines[i].begin(), lines[i].end());
            set_intersection(prev_items.begin(), prev_items.end(),
                             curr_items.begin(), curr_items.end(),
                             inserter(common_items1, common_items1.begin()));
        }
        if (i % 3 == 2) {
            set<char> curr_items(lines[i].begin(), lines[i].end());
            set_intersection(common_items1.begin(), common_items1.end(),
                             curr_items.begin(), curr_items.end(),
                             inserter(common_items2, common_items2.begin()));
            for (char common_char : common_items2) {
                int priority = common_char >= 'a' ? common_char - 'a' + 1 : common_char - 'A' + 27;
                result += priority;
            }
            common_items1 = {};
            common_items2 = {};
        }
    }
    return result;
}
