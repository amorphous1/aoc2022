#include <iostream>
#include <vector>
#include <fstream>
#include "day01.cpp"

using namespace std;

vector<string> read_lines(const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "cannot open file " << file_name << endl;
        exit(1);
    }
    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return lines;
}

// https://stackoverflow.com/questions/35888818/why-are-my-breakpoints-not-hit-in-clion
int main() {
    cout << day01a(read_lines("inputs/day01.input")) << endl;
    cout << day01b(read_lines("inputs/day01.input")) << endl;
    return 0;
}
