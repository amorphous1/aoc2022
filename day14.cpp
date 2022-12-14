#include <algorithm>
#include <deque>
#include <map>
#include <string>
#include <vector>
#include "common.h"

using namespace std;

vector<Coord> connecting_points(const Coord& a, const Coord& b) {
    vector<Coord> result = { b };
    int dx = a.x < b.x ? 1 : a.x > b.x ? -1 : 0, dy = a.y < b.y ? 1 : a.y > b.y ? -1 : 0;
    for (Coord c = a; c != b; c = { c.x + dx, c.y + dy }) {
        result.push_back(c);
    }
    return result;
}

struct Cave {
    map<Coord, char> tiles;
    int min_x = INT32_MAX, max_y = -1;
};

bool pour_sand(Cave& cave, const Coord& start) {
    Coord current = start;
    while (current.y <= cave.max_y) {
        if (!cave.tiles.contains({current.x, current.y+1})) current = { current.x, current.y+1 };
        else if (!cave.tiles.contains({current.x-1, current.y+1})) current = { current.x-1, current.y+1 };
        else if (!cave.tiles.contains({current.x+1, current.y+1})) current = { current.x+1, current.y+1 };
        else {
            cave.tiles[current] = 'o';
            return true;
        }
    }
    return false;
}

bool pour_sand_2(Cave& cave, const Coord& start) {
    Coord current = start;
    while (current.y <= cave.max_y) {
        if (!cave.tiles.contains({current.x, current.y+1})) current = { current.x, current.y+1 };
        else if (!cave.tiles.contains({current.x-1, current.y+1})) current = { current.x-1, current.y+1 };
        else if (!cave.tiles.contains({current.x+1, current.y+1})) current = { current.x+1, current.y+1 };
        else {
            cave.tiles[current] = 'o';
            return true;
        }
    }
    if (current.y == cave.max_y + 1) {
        cave.tiles[current] = 'o';
    }
    return false;
}

int day14a(const vector<string>& scans) {
    Cave cave;

    for (const string& scan : scans) {
        vector<Coord> coords;
        for (const string& coord : split(scan, " -> ")) {
            vector<string> xy = split(coord, ",");
            coords.push_back({ stoi(xy[0]), stoi(xy[1]) });
        }
        for (int i = 0; i < coords.size() - 1; i++) {
            for (const Coord& coord : connecting_points(coords[i], coords[i+1])) {
                cave.tiles[coord] = '#';
                cave.min_x = min(cave.min_x, coord.x);
                cave.max_y = max(cave.max_y, coord.y);
            }
        }
    }
    int result = 0;
    while (pour_sand(cave, {500, 0})) {
        result++;
    }
    return result;
}

int day14b(const vector<string>& scans) {
    Cave cave;

    for (const string& scan : scans) {
        vector<Coord> coords;
        for (const string& coord : split(scan, " -> ")) {
            vector<string> xy = split(coord, ",");
            coords.push_back({ stoi(xy[0]), stoi(xy[1]) });
        }
        for (int i = 0; i < coords.size() - 1; i++) {
            for (const Coord& coord : connecting_points(coords[i], coords[i+1])) {
                cave.tiles[coord] = '#';
                cave.min_x = min(cave.min_x, coord.x);
                cave.max_y = max(cave.max_y, coord.y);
            }
        }
    }
    int result = 0;
    while (!cave.tiles.contains({500,0})) {
        pour_sand_2(cave, {500,0});
        result++;
    }
    return result;
}



