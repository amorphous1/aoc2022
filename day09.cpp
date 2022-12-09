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

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
    Point operator+(const Point& other) const {
        return { other.x + x, other.y + y };
    }
    [[nodiscard]] Point add(const Point& other) const {
        return { other.x + x, other.y + y };
    }
    [[nodiscard]] bool is_adjacent_to(const Point& other) const {
        return abs(other.x - x) < 2 && abs(other.y - y) < 2;
    }
    [[nodiscard]] Point follow(const Point& other) const {
        if (abs(x - other.x) > 1 && abs(y - other.y) > 1) return { other.x + sgn(x - other.x), other.y + sgn(y - other.y) };
        if (abs(x - other.x) > 1) return { other.x + sgn(x - other.x), other.y };
        if (abs(y - other.y) > 1) return { other.x, other.y + sgn(y - other.y) };
        return { x, y };
    }
    [[nodiscard]] Point inverse() const {
        return { -1 * x, -1 * y};
    }
};

ulong day09a(const vector<string>& lines) {
    const map<string, Point> directions = { {"R", {1,0}}, {"L", {-1,0}}, {"U", {0,1}}, {"D", {0,-1}} };
    Point head = {0,0}, tail = {0,0};
    set<Point> tail_positions = { tail };

    for (const string& line : lines) {
        vector<string> tokens = split(line, " ");
        Point direction = directions.at(tokens[0]);
        int steps = stoi(tokens[1]);
        for (int step = 1; step <= steps; step++) {
            head = head + direction;
            if (!head.is_adjacent_to(tail)) {
                tail = head + direction.inverse();
                tail_positions.insert(tail);
            }
        }
    }
    return tail_positions.size();
}

ulong day09b(const vector<string>& lines) {
    map<string, Point> directions = { {"R", {1,0}}, {"L", {-1,0}}, {"U", {0,1}}, {"D", {0,-1}} };
    Point rope[] = { {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} };
    set<Point> tail_positions = { {0,0} };

    for (const string& line : lines) {
        vector<string> tokens = split(line, " ");
        Point direction = directions.at(tokens[0]);
        int steps = stoi(tokens[1]);
        for (int step = 0; step < steps; step++) {
            rope[0] = rope[0] + direction;
            for (int knot = 1; knot < 10; knot++) {
                rope[knot] = rope[knot].follow(rope[knot-1]);
            }
            tail_positions.insert(rope[9]);
        }
    }
    return tail_positions.size();
}
