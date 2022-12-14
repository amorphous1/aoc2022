#include <iostream>
#include <vector>
#include <fstream>
//#include "day01.cpp"
//#include "day02.cpp"
//#include "day03.cpp"
//#include "day04.cpp"
//#include "day05.cpp"
//#include "day06.cpp"
//#include "day07.cpp"
//#include "day08.cpp"
//#include "day09.cpp"
//#include "day10.cpp"
//#include "day11.cpp"
//#include "day12.cpp"
//#include "day13.cpp"
//#include "day14.cpp"
//#include "day15.cpp"
#include "day17.cpp"

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
//    cout << day03a(read_lines("inputs/day03.input")) << endl;  // 7917
//    cout << day03b(read_lines("inputs/day03.input")) << endl;  // 2585
//    const pair<int, int> &day4 = day04(read_lines("inputs/day04.input"));
//    cout << day4.first << " " << day4.second << endl;  // 524 798
//    stack<char> s1({ 'Q','M','G','C','L', }),
//                s2({ 'R','D','L','C','T','F','H','G', }),
//                s3({ 'V','J','F','N','M','T','W','R', }),
//                s4({ 'J','F','D','V','Q','P', }),
//                s5({ 'N','F','M','S','L','B','T', }),
//                s6({ 'R','N','V','H','C','D','P', }),
//                s7({ 'H','C','T', }),
//                s8({ 'G','S','J','V','Z','N','H','P', }),
//                s9({ 'Z','F','H','G' });
//    vector<stack<char>> stacks = { s1, s2, s3, s4, s5, s6, s7, s8, s9 };
//    cout << day05a(stacks, read_lines("inputs/day05.input")) << endl;  // VCTFTJQCG
//    cout << day05b(stacks, read_lines("inputs/day05.input")) << endl;  // GCFGLDNJZ
//    cout << day06a(read_lines("inputs/day06.input").at(0)) << endl;  // 1651
//    cout << day06b(read_lines("inputs/day06.input").at(0)) << endl;  // 3837
//    cout << day07a(read_lines("inputs/day07.input")) << endl;  // 1543140
//    cout << day07b(read_lines("inputs/day07.input")) << endl;  // 1117448
//    cout << day08a(read_lines("inputs/day08.input")) << endl;  // 1690
//    cout << day08b(read_lines("inputs/day08.input")) << endl;  // 535680
//    cout << day09a(read_lines("inputs/day09.input")) << endl;  // 6026
//    cout << day09b(read_lines("inputs/day09.input")) << endl;  // 2273
//    cout << day10a(read_lines("inputs/day10.input")) << endl;  // 13520
//    vector<string> screen = day10b(read_lines("inputs/day10.input"));  // PGPHBEAB
//    for (const string& row : screen) cout << row << endl;
//    cout << day11a(read_lines("inputs/day11.input")) << endl;  // 316888
//    cout << day11b(read_lines("inputs/day11.input")) << endl;  // 35270398814
//    cout << day12a(read_lines("inputs/day12.input")) << endl;  // 383
//    cout << day12b(read_lines("inputs/day12.input")) << endl;  // 377
//    cout << day13a(read_lines("inputs/day13.input")) << endl;  // 6272
//    cout << day13b(read_lines("inputs/day13.input")) << endl;  // 22288
//    cout << day14a(read_lines("inputs/day14.input")) << endl;  // 665
//    cout << day14b(read_lines("inputs/day14.input")) << endl;  // 25434
//    cout << day15a(read_lines("inputs/day15.input"), 2000000) << endl;  // 5688618
//    cout << day15b(read_lines("inputs/day15.input"), 4000000) << endl;  // 12625383204261
    cout << day17a(read_lines("inputs/day17.input")[0]) << endl;  // 3197
    cout << day17b(read_lines("inputs/day17.input")[0]) << endl;  // 1568513119571
    return 0;
}
