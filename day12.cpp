#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Coord {
    int x, y;

    bool operator<(const Coord& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

Coord remove_closest_to_start(set<Coord>& edge, const map<Coord, int>& distance_from_start) {
    Coord closest_to_start = *edge.begin();
    for (const Coord& candidate : edge) {
        if (distance_from_start.at(candidate) < distance_from_start.at(closest_to_start)) {
            closest_to_start = candidate;
        }
    }
    edge.erase(closest_to_start);
    return closest_to_start;
}
vector<Coord> find_neighbours(Coord current, const vector<string>& heightmap, const map<Coord, int>& distance_from_start) {
    vector<Coord> neighbours;
    for (Coord delta : vector<Coord>{ {0,1}, {0,-1}, {1,0}, {-1,0} }) {
        Coord neighbour = { current.x + delta.x, current.y + delta.y };
        if (neighbour.y >= 0 && neighbour.y < heightmap.size() &&
            neighbour.x >= 0 && neighbour.x < heightmap[0].size() &&
            !distance_from_start.contains(neighbour) &&
            heightmap[neighbour.y][neighbour.x] - heightmap[current.y][current.x] < 2) {
            neighbours.push_back(neighbour);
        }
    }
    return neighbours;
}
int day12a(vector<string> heightmap) {
    Coord start{}, end{};
    for (int y = 0; y < heightmap.size(); y++) {
        for (int x = 0; x < heightmap[y].size(); x++) {
            if (heightmap[y][x] == 'S') {
                heightmap[y][x] = 'a';
                start = { x, y };
            }
            if (heightmap[y][x] == 'E') {
                heightmap[y][x] = 'z';
                end = { x, y };
            }
        }
    }
    set<Coord> edge = { start };
    map<Coord, int> distance_from_start = { {start,0} };
    while (!edge.empty() && !distance_from_start.contains(end)) {
        Coord current = remove_closest_to_start(edge, distance_from_start); // ;
        for (Coord neighbour : find_neighbours(current, heightmap, distance_from_start)) {
            distance_from_start[neighbour] = distance_from_start[current] + 1;
            edge.insert(neighbour);
            cout << "inserting " << neighbour.x << "," << neighbour.y << " with distance from start " << distance_from_start[neighbour] << " - new edge size " << edge.size() << endl;
        }
    }
    cout << edge.size() << " " << distance_from_start.contains(end) << endl;
    return distance_from_start[end];
}
