#include <string>
#include <vector>
#include "common.h"

using namespace std;

struct Cpu {
    int cycle = 0, x = 1, signal = 0;
    vector<string> screen = {
            "                                        ",
            "                                        ",
            "                                        ",
            "                                        ",
            "                                        ",
            "                                        ",
    };
    void advance_cycles(int steps) {
        for (int i = 0; i < steps; i++) {
            cycle++;
            signal += (cycle == 20 || (cycle - 20) % 40 == 0) ? cycle * x : 0;
            int col = (cycle-1) % 40, row = (cycle-1) / 40;
            screen.at(row)[col] = (abs(col - x) < 2) ? '#' : '.';
        }
    }
    void addx(int delta) {
        advance_cycles(2);
        x += delta;
    }
    static Cpu execute(const vector<string>& instructions) {
        Cpu cpu;
        for (const string& line : instructions) {
            vector<string> tokens = split(line, " ");
            string instruction = tokens[0];
            if (instruction == "noop") cpu.advance_cycles(1);
            if (instruction == "addx") cpu.addx(stoi(tokens[1]));
        }
        return cpu;
    }
};

int day10a(const vector<string>& instructions) {
    return Cpu::execute(instructions).signal;
}

vector<string> day10b(const vector<string>& instructions) {
    return Cpu::execute(instructions).screen;
}
