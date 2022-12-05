#pragma once
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