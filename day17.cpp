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
            if (tile.x + dx < 0 || tile.x + dx > max_x || chamber.contains({tile.x + dx, tile.y}))
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

struct Chamber {
    string jets;
    set<Coord> filled;
    int max_height = 0, rock = 0, jet = 0;

    static constexpr int MAX_X = 6, INITIAL_DX = 2, INITIAL_DY = 4;
    const Rock MINUS    = { {{0, 0}, {1, 0}, {2, 0}, {3, 0}} };
    const Rock PLUS     = { {{0, 1}, {1, 0}, {1, 1}, {1, 2}, {2, 1}} };
    const Rock MIRROR_L = { {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}} };
    const Rock I        = { {{0, 0}, {0, 1}, {0, 2}, {0, 3}} };
    const Rock SQUARE   = { {{0, 0}, {0, 1}, {1, 0}, {1, 1}} };
    const vector<Rock> ROCKS = {MINUS, PLUS, MIRROR_L, I, SQUARE };

    void place_next_rock() {
        Rock next_rock = Rock::at_pos({INITIAL_DX, max_height+INITIAL_DY}, ROCKS[rock]);
        bool fell_down;
        do {
            next_rock.push(jets[jet] == '<' ? -1 : 1, filled, MAX_X);
            jet = (jet + 1) % (int)jets.size();
            fell_down = next_rock.fall(filled);
        } while (fell_down);
        rock = (rock + 1) % (int)ROCKS.size();
        for (const Coord& tile : next_rock.tiles) {
            filled.insert(tile);
            max_height = max(tile.y, max_height);
        }
    }
};

int day17a(const string& jets) {
    Chamber chamber = Chamber{ jets };
    for (int i = 0; i < 2022; i++)
        chamber.place_next_rock();
    return chamber.max_height;
}