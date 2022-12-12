#include <map>
#include <set>
#include <string>
#include <vector>

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
vector<Coord> find_neighbours(const Coord& current, const vector<string>& heightmap, const map<Coord, int>& distance_from_start) {
    vector<Coord> neighbours;
    for (Coord delta : vector<Coord>{ {0,1}, {0,-1}, {1,0}, {-1,0} }) {
        Coord neighbour = { current.x + delta.x, current.y + delta.y };
        if (neighbour.y >= 0 && neighbour.y < heightmap.size() && neighbour.x >= 0 && neighbour.x < heightmap[0].size() &&
            !distance_from_start.contains(neighbour) && heightmap[neighbour.y][neighbour.x] - heightmap[current.y][current.x] < 2) {
            neighbours.push_back(neighbour);
        }
    }
    return neighbours;
}
int day12(vector<string> heightmap, const set<char>& start_chars) {
    vector<Coord> start_candidates;
    Coord end{};
    for (int y = 0; y < heightmap.size(); y++) {
        for (int x = 0; x < heightmap[y].size(); x++) {
            if (start_chars.contains(heightmap[y][x])) {
                heightmap[y][x] = 'a';
                start_candidates.push_back({ x, y });
            }
            if (heightmap[y][x] == 'E') {
                heightmap[y][x] = 'z';
                end = { x, y };
            }
        }
    }
    int shortest_path = 99999;
    for (Coord start : start_candidates) {
        set<Coord> edge = { start };
        map<Coord, int> distance_from_start = { {start,0} };
        while (!edge.empty() && !distance_from_start.contains(end)) {
            Coord current = remove_closest_to_start(edge, distance_from_start); // ;
            for (Coord neighbour : find_neighbours(current, heightmap, distance_from_start)) {
                distance_from_start[neighbour] = distance_from_start[current] + 1;
                edge.insert(neighbour);
            }
        }
        shortest_path = distance_from_start.contains(end) && distance_from_start[end] < shortest_path ? distance_from_start[end] : shortest_path;
    }
    return shortest_path;
}

int day12a(const vector<string>& heightmap) {
    return day12(heightmap, {'S'});
}
int day12b(const vector<string>& heightmap) {
    return day12(heightmap, {'S', 'a'});
}