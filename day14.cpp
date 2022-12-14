#include <map>
#include <string>
#include <vector>
#include "common.h"

using namespace std;

struct Cave {
    map<Coord, char> tiles;
    int max_y = -1;

    static vector<Coord> connecting_points(const Coord& a, const Coord& b) {
        vector<Coord> result = { b };
        int dx = sgn(b.x - a.x), dy = sgn(b.y - a.y);
        for (Coord c = a; c != b; c = { c.x + dx, c.y + dy }) {
            result.push_back(c);
        }
        return result;
    }

    static Cave parse(const vector<string>& scans) {
        Cave cave;
        for (const string& scan : scans) {
            auto nums = find_numbers<vector<int>>(scan);
            for (int i = 3; i < nums.size(); i+= 2) {
                for (const Coord& coord : connecting_points({nums[i-3], nums[i-2]}, {nums[i-1], nums[i]})) {
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
    for (result = 0; cave.pour_sand({500, 0}); result++);
    return result;
}

int day14b(const vector<string>& scans) {
    Cave cave = Cave::parse(scans);
    int result;
    for (result = 0; !cave.tiles.contains({500,0}); result++) {
        cave.pour_sand({500,0});
    }
    return result;
}