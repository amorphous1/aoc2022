#include <string>
#include <vector>
#include "common.h"

using namespace std;

struct Cpu {
    int cycle = 0, x = 1, signal = 0;
    vector<string> screen = {
            "........................................",
            "........................................",
            "........................................",
            "........................................",
            "........................................",
            "........................................",
    };

    void advance_cycles(int delta) {
        for (int i = 0; i < delta; i++) {
            cycle++;
            if (cycle == 20 || (cycle - 20) % 40 == 0) {
                signal += cycle * x;
            }
            int col = (cycle-1) % 40;
            if (abs(col - x) < 2) {
                int row = (cycle-1) / 40;
                cout << "cycle=" << cycle << " row=" << row << " col=" << col << endl;
                screen.at(row)[col] = '#';
            }
        }
    }
    void noop() {
        advance_cycles(1);
        cout << "noop - " << cycle << ", X=" << x << ", signal=" << signal << endl;
    }
    void addx(int delta) {
        advance_cycles(2);
        x += delta;
        cout << "addx " << delta << " - " << cycle << ", X=" << x << ", signal=" << signal << endl;
    }
};

int day10a(const vector<string>& lines) {
    Cpu cpu = { 0, 1, 0};
    for (const string& line : lines) {
        vector<string> tokens = split(line, " ");
        string instruction = tokens[0];
        if (instruction == "noop") cpu.noop();
        if (instruction == "addx") cpu.addx(stoi(tokens[1]));
    }
    for (string row : cpu.screen) {
        cout << row << endl;
    }
    return cpu.signal;
}
