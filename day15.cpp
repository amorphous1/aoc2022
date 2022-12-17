#include <deque>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "common.h"

using namespace std;

int distance_between(const Coord& a, const Coord& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

struct RangeSet {
    deque<pair<int, int>> ranges;

    void insert(int from, int to) {
        for (int i = 0; i < ranges.size(); i++) {
            if (to < ranges[i].first - 1) { // strictly smaller than current range, insert at current position
                ranges.insert(ranges.begin() + i, make_pair(from, to));
                return;
            }
            if (from <= ranges[i].second + 1) { // overlap with current range, merge them
                ranges[i] = make_pair(min(ranges[i].first, from), max(ranges[i].second, to));
                while (i+1 < ranges.size() && ranges[i].second >= ranges[i+1].first - 1) { // merge all subsequent overlaps
                    ranges[i].second = max(ranges[i].second, ranges[i+1].second);
                    ranges.erase(ranges.begin() + i + 1);
                }
                return;
            }
            // strictly greater than current range, just continue
        }
        ranges.emplace_back(from, to);  // strictly greater than all existing ranges, insert at the end
    }
    ulong size() {
        ulong result = 0;
        for (const pair<int, int>& range : ranges) {
            result += range.second - range.first + 1;
        }
        return result;
    }
};

ulong day15a(const vector<string>& lines, int target_row) {
    set<Coord> beacons_at_target_row;
    RangeSet monitoring_at_target_row;
    for (const string& line : lines) {
        const auto nums = find_numbers<vector<int>>(line, true);
        Coord scanner = { nums[0], nums[1] }, nearest_beacon = { nums[2], nums[3] };
        if (nearest_beacon.y == target_row) {
            beacons_at_target_row.insert(nearest_beacon);
        }
        int distance_to_beacon = distance_between(scanner, nearest_beacon), distance_to_target_row = abs(scanner.y - target_row);
        if (distance_to_target_row <= distance_to_beacon) {
            int extra_monitored_spaces = abs(distance_to_beacon - distance_to_target_row);
            monitoring_at_target_row.insert(scanner.x - extra_monitored_spaces, scanner.x + extra_monitored_spaces);
        }
    }
    return monitoring_at_target_row.size() - beacons_at_target_row.size();
}

unsigned long long day15b(const vector<string>& lines, int max_coord) {
    map<int, RangeSet> monitoring_by_row;
    for (const string& line : lines) {
        const auto nums = find_numbers<vector<int>>(line, true);
        Coord scanner = { nums[0], nums[1] }, nearest_beacon = { nums[2], nums[3] };
        int distance_to_beacon = distance_between(scanner, nearest_beacon);
        for (int dy = 0; dy <= distance_to_beacon; dy++) {
            if (scanner.y + dy >= 0 && scanner.y + dy <= max_coord)
                monitoring_by_row[scanner.y + dy].insert(max(0, scanner.x - distance_to_beacon + dy), min(scanner.x + distance_to_beacon - dy, max_coord));
            if (scanner.y - dy >= 0 && scanner.y - dy <= max_coord)
                monitoring_by_row[scanner.y - dy].insert(max(0, scanner.x - distance_to_beacon + dy), min(scanner.x + distance_to_beacon - dy, max_coord));
        }
    }
    for (const auto& [y, ranges] : monitoring_by_row) {
        if (ranges.ranges.size() > 1) return 4000000uL * (ranges.ranges[0].second + 1) + y;
    }
    return 0;
}

