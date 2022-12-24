#include <map>
#include <set>
#include <string>
#include <vector>
#include "common.h"

using namespace std;

struct Rock {
    vector<Coord> tiles;

    static Rock at_pos(const Coord& pos, const Rock& shape) {
        Rock rock(shape);
        for (Coord& tile : rock.tiles)
            tile = {tile.x + pos.x, tile.y + pos.y};
        return rock;
    }

    void push(const int dx, const set<Coord>& chamber, const int max_x) {
        for (Coord& tile : tiles)
            if ((tile.x == 0 && dx < 0) || tile.x + dx > max_x || chamber.contains({tile.x + dx, tile.y}))
                return;
        for (Coord& tile : tiles)
            tile.x += dx;
    }

    bool fall(const set<Coord>& chamber) {
        for (const Coord& tile : tiles)
            if (tile.y == 1 || chamber.contains({tile.x, tile.y-1}))
                return false;
        for (Coord& tile : tiles)
            tile.y -= 1;
        return true;
    }
};

struct ChamberFingerprint {
    int rock, jet;
    set<Coord> top_filled;
    bool operator<(const ChamberFingerprint& other) const {
        return rock < other.rock || (rock == other.rock && jet < other.jet) || (rock == other.rock && jet == other.jet && top_filled < other.top_filled);
    }
    static ChamberFingerprint from(int max_height, int rock, int jet, const set<Coord>& filled) {
        set<Coord> top_filled;
        for (Coord point : filled)
            if (point.y >= max_height - 7)
                top_filled.insert({point.x, max_height - point.y});
        return { rock, jet, top_filled };
    }
};

struct Chamber {
    string jets;
    set<Coord> filled;
    int top, rock = 0, jet = 0;

    static constexpr int MAX_X = 6, INITIAL_DX = 2, INITIAL_DY = 4;
    const Rock MINUS    = { {{0, 0}, {1, 0}, {2, 0}, {3, 0}} };
    const Rock PLUS     = { {{0, 1}, {1, 0}, {1, 1}, {1, 2}, {2, 1}} };
    const Rock MIRROR_L = { {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}} };
    const Rock I        = { {{0, 0}, {0, 1}, {0, 2}, {0, 3}} };
    const Rock SQUARE   = { {{0, 0}, {0, 1}, {1, 0}, {1, 1}} };
    const vector<Rock> ROCKS = {MINUS, PLUS, MIRROR_L, I, SQUARE };

    ChamberFingerprint place_next_rock() {
        Rock next_rock = Rock::at_pos({INITIAL_DX, top + INITIAL_DY}, ROCKS[rock]);
        bool fell_down;
        do {
            next_rock.push(jets[jet] == '<' ? -1 : 1, filled, MAX_X);
            jet = (jet + 1) % (int)jets.size();
            fell_down = next_rock.fall(filled);
        } while (fell_down);
        rock = (rock + 1) % (int)ROCKS.size();
        for (const Coord& tile : next_rock.tiles) {
            filled.insert(tile);
            top = max(tile.y, top);
        }
        return ChamberFingerprint::from(top, rock, jet, filled);
    }
};

ulong day17(const string& jets, const ulong iterations) {
    Chamber chamber = Chamber{ jets };
    map<ChamberFingerprint, pair<int, int>> fingerprint_to_iteration_and_height;
    for (ulong i = 1; i <= iterations ; i++) {
        ChamberFingerprint fingerprint = chamber.place_next_rock();
        if (fingerprint_to_iteration_and_height.contains(fingerprint)) {
            auto [prev_i, prev_top] = fingerprint_to_iteration_and_height[fingerprint];
            ulong delta_i = i - prev_i, delta_top = chamber.top - prev_top;
            ulong extra_cycles = (iterations - i) / delta_i, extra_steps = iterations - i - extra_cycles * delta_i;
            for (int j = 1; j <= extra_steps; j++)
                chamber.place_next_rock();
            return chamber.top + extra_cycles * delta_top;
        }
        fingerprint_to_iteration_and_height[fingerprint] = make_pair(i, chamber.top);
    }
    return chamber.top;
}
ulong day17a(const string& jets) {
    return day17(jets, 2022);
}
ulong day17b(const string& jets) {
    return day17(jets, 1000000000000);
}
