#include <map>
#include <set>
#include <string>
#include <vector>
#include "common.h"

using namespace std;

int sgn(int x) {
    return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

struct Point {
    int x, y;

    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
    Point operator+(const Point& other) const {
        return { other.x + x, other.y + y };
    }
    [[nodiscard]] Point follow(const Point& other) const {
        if (abs(x - other.x) > 1 && abs(y - other.y) > 1) return { other.x + sgn(x - other.x), other.y + sgn(y - other.y) };
        if (abs(x - other.x) > 1) return { other.x + sgn(x - other.x), other.y };
        if (abs(y - other.y) > 1) return { other.x, other.y + sgn(y - other.y) };
        return { x, y };
    }
};

ulong day09(const vector<string>& lines, int knots) {
    map<string, Point> directions = { {"R", {1,0}}, {"L", {-1,0}}, {"U", {0,1}}, {"D", {0,-1}} };
    vector<Point> rope;
    for (int knot = 0; knot < knots; knot++) rope.push_back({0,0});
    set<Point> tail_positions = { {0,0} };

    for (const string& line : lines) {
        vector<string> tokens = split(line, " ");
        Point direction = directions.at(tokens[0]);
        int steps = stoi(tokens[1]);
        for (int step = 0; step < steps; step++) {
            rope[0] = rope[0] + direction;
            for (int knot = 1; knot < knots; knot++) {
                rope[knot] = rope[knot].follow(rope[knot-1]);
            }
            tail_positions.insert(rope[knots-1]);
        }
    }
    return tail_positions.size();
}

ulong day09a(const vector<string>& lines) {
    return day09(lines, 2);
}
ulong day09b(const vector<string>& lines) {
    return day09(lines, 10);
}
