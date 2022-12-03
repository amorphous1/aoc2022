#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

set<char> common_chars(const string& s1, const string& s2) {
    set<char> chars1(s1.begin(), s1.end()), chars2(s2.begin(), s2.end()), common;
    set_intersection(chars1.begin(), chars1.end(), chars2.begin(), chars2.end(), inserter(common, common.begin()));
    return common;
}
set<char> common_chars(const string& s1, const string& s2, const string& s3) {
    set<char> common12 = common_chars(s1, s2);
    string s12(common12.begin(), common12.end());
    return common_chars(s12, s3);
}
int priority(const set<char>& items) {
    int result = 0;
    for (char item : items) {
        result += item >= 'a' ? item - 'a' + 1 : item - 'A' + 27;
    }
    return result;
}

int day03a(const vector<string>& lines) {
    int result = 0;
    for (const string& line : lines) {
        string compartment1 = line.substr(0, line.length() / 2);
        string compartment2 = line.substr(line.length() / 2);
        result += priority(common_chars(compartment1, compartment2));
    }
    return result;
}

int day03b(const vector<string>& lines) {
    int result = 0;
    for (int i = 2; i < lines.size(); i += 3) {
        result += priority(common_chars(lines[i-2], lines[i-1], lines[i]));
    }
    return result;
}
