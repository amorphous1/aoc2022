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
    int max_y = -1;

    static Cave parse(const vector<string>& scans) {
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
                    cave.max_y = max(cave.max_y, coord.y);
                }
            }
        }
        return cave;
    }

    bool pour_sand(const Coord& start) {
        Coord current = start;
        while (current.y <= max_y) {
            if (!tiles.contains({current.x, current.y+1})) current = { current.x, current.y+1 };
            else if (!tiles.contains({current.x-1, current.y+1})) current = { current.x-1, current.y+1 };
            else if (!tiles.contains({current.x+1, current.y+1})) current = { current.x+1, current.y+1 };
            else {
                tiles[current] = 'o';
                return true;
            }
        }
        if (current.y == max_y + 1) {
            tiles[current] = 'o';
        }
        return false;
    }
};

int day14a(const vector<string>& scans) {
    Cave cave = Cave::parse(scans);
    int result = 0;
    while (cave.pour_sand({500, 0})) {
        result++;
    }
    return result;
}

int day14b(const vector<string>& scans) {
    Cave cave = Cave::parse(scans);
    int result = 0;
    while (!cave.tiles.contains({500,0})) {
        cave.pour_sand({500,0});
        result++;
    }
    return result;
}
