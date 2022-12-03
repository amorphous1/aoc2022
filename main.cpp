#include <iostream>
#include <vector>
#include <fstream>
//#include "day01.cpp"
//#include "day02.cpp"
#include "day03.cpp"

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
//    cout << day01a(read_lines("inputs/day01.input")) << endl;
//    cout << day01b(read_lines("inputs/day01.input")) << endl;
//    cout << day02a(read_lines("inputs/day02.input")) << endl;
//    cout << day02b(read_lines("inputs/day02.input")) << endl;
    cout << day03a(read_lines("inputs/day03.input")) << endl;  // 7917
    cout << day03b(read_lines("inputs/day03.input")) << endl;  // 2585
    return 0;
}
