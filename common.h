#pragma once
#include <string>
#include <vector>
#include <cassert>

using namespace std;

template<class C>
C find_numbers(const string& str) {
    C numbers;
    char const* digits = "0123456789";
    size_t start, end = 0;
    do {
        start = str.find_first_of(digits, end);
        end = str.find_first_not_of(digits, start);
        if (start != string::npos)
            numbers.push_back(stoi(str.substr(start, end != string::npos ? end-start : end)));
    } while (end != string::npos);
    return numbers;
}
int find_number(const string& str) {
    auto numbers = find_numbers<vector<int>>(str);
    assert(numbers.size() == 1);
    return numbers[0];
}

vector<string> split(const string& s, const string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    if (delimiter.empty()) {
        for (char c: s) {
            token = string(1, c);
            res.push_back(token);
        }
        return res;
    }

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        if (!token.empty()) {
            res.push_back(token);
        }
    }
    res.push_back(s.substr(pos_start));
    return res;
}
