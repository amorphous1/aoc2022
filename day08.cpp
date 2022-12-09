#include <string>
#include <vector>

using namespace std;

bool all_smaller(int x, int y, int dx, int dy, const vector<string>& trees) {
    int tree_height = trees.at(y)[x] - '0';
    int nx = x + dx, ny = y + dy;
    while (ny >=0 && ny < trees.size() && nx >= 0 && nx < trees.at(ny).size()) {
        int other_height = trees.at(ny)[nx] - '0';
        if (other_height >= tree_height) return false;
        nx = nx + dx, ny = ny + dy;
    }
    return true;
}

bool is_visible(int x, int y, const vector<string>& trees) {
    return all_smaller(x, y, -1, 0, trees) || all_smaller(x, y, 1, 0, trees) ||
           all_smaller(x, y, 0, -1, trees) || all_smaller(x, y, 0, 1, trees);
}

int scenic_score(int x, int y, int dx, int dy, const vector<string>& trees) {
    int tree_height = trees.at(y)[x] - '0';
    int nx = x + dx, ny = y + dy;
    int result = 0;
    while (ny >=0 && ny < trees.size() && nx >= 0 && nx < trees.at(ny).size()) {
        result++;
        int other_height = trees.at(ny)[nx] - '0';
        if (other_height >= tree_height) return result;
        nx = nx + dx, ny = ny + dy;
    }
    return result;
}

int scenic_score(int x, int y, const vector<string>& trees) {
    return scenic_score(x, y, -1, 0, trees) * scenic_score(x, y, 1, 0, trees) *
           scenic_score(x, y, 0, -1, trees) * scenic_score(x, y, 0, 1, trees);
}

int day08a(const vector<string>& lines) {
    int result = 0;
    for (int y = 0; y < lines.size(); y++) {
        for (int x = 0; x < lines.at(y).size(); x++) {
            if (is_visible(x, y, lines)) {
                result++;
            }
        }
    }
    return result;
}

int day08b(const vector<string>& lines) {
    int result = 0;
    for (int y = 0; y < lines.size(); y++) {
        for (int x = 0; x < lines.at(y).size(); x++) {
            result = max(result, scenic_score(x, y, lines));
        }
    }
    return result;
}
