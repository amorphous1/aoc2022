#include <string>
#include <set>

using namespace std;

int day06(const string& input, int num_distinct) {
    for (int i = num_distinct - 1; i < input.length(); i++) {
        set<char> last_chars = {};
        for (int j = 0; j < num_distinct; j++) {
            last_chars.insert(input[i-j]);
        }
        if (last_chars.size() == num_distinct) {
            return i + 1;
        }
    }
    return -1;
}

int day06a(const string& input) {
    return day06(input, 4);
}

int day06b(const string& input) {
    return day06(input, 14);
}
