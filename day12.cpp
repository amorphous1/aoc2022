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

Coord remove_closest_to_end(set<Coord>& edge, const map<Coord, int>& distance_to_end) {
    Coord closest_to_end = *edge.begin();
    for (const Coord& candidate : edge) {
        if (distance_to_end.at(candidate) < distance_to_end.at(closest_to_end)) {
            closest_to_end = candidate;
        }
    }
    edge.erase(closest_to_end);
    return closest_to_end;
}

vector<Coord> find_neighbours(const Coord& current, const vector<string>& heights, const map<Coord, int>& distance_to_end) {
    vector<Coord> neighbours;
    for (Coord delta : vector<Coord>{ {0,1}, {0,-1}, {1,0}, {-1,0} }) {
        Coord neighbour = { current.x + delta.x, current.y + delta.y };
        if (neighbour.y >= 0 && neighbour.y < heights.size() && neighbour.x >= 0 && neighbour.x < heights[0].size() &&
            !distance_to_end.contains(neighbour) && heights[current.y][current.x] - heights[neighbour.y][neighbour.x] < 2) {
            neighbours.push_back(neighbour);
        }
    }
    return neighbours;
}

int day12(vector<string> heights, const set<char>& start_chars) {
    vector<Coord> start_candidates;
    Coord end{};
    for (int y = 0; y < heights.size(); y++) {
        for (int x = 0; x < heights[y].size(); x++) {
            if (start_chars.contains(heights[y][x])) {
                heights[y][x] = 'a';
                start_candidates.push_back({ x, y });
            }
            if (heights[y][x] == 'E') {
                heights[y][x] = 'z';
                end = { x, y };
            }
        }
    }
    set<Coord> edge = { end };
    map<Coord, int> distance_to_end = { {end,0} };
    while (!edge.empty()) {
        Coord current = remove_closest_to_end(edge, distance_to_end);
        for (Coord neighbour : find_neighbours(current, heights, distance_to_end)) {
            distance_to_end[neighbour] = distance_to_end[current] + 1;
            edge.insert(neighbour);
        }
    }
    int shortest_path = INT32_MAX;
    for (const Coord& start : start_candidates) {
        shortest_path = distance_to_end.contains(start) && distance_to_end[start] < shortest_path ? distance_to_end[start] : shortest_path;
    }
    return shortest_path;
}

int day12a(const vector<string>& heights) {
    return day12(heights, {'S'});
}
int day12b(const vector<string>& heights) {
    return day12(heights, {'S', 'a'});
}