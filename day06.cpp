#include <string>
#include <set>

using namespace std;

int day06a(string input) {
    for (int i = 3; i < input.length(); i++) {
        set<char> last_four = { input[i], input[i-1], input[i-2], input[i-3] };
        if (last_four.size() == 4) {
            return i + 1;
        }
    }
    return -1;
}

int day06b(string input) {
    for (int i = 14 - 1; i < input.length(); i++) {
        set<char> last_chars = {};
        for (int j = 0; j < 14; j++) {
            last_chars.insert(input[i-j]);
        }
        if (last_chars.size() == 14) {
            return i + 1;
        }
    }
    return -1;
}
