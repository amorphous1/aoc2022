#include <string>
#include <vector>
#include <stack>
#include "common.h"

using namespace std;

string day05a(vector<stack<char>>& stacks, const vector<string>& moves) {
    for (const string& move : moves) {
        auto num_from_to = find_numbers<vector<int>>(move);
        stack<char>& source = stacks.at(num_from_to.at(1) - 1);
        stack<char>& target = stacks.at(num_from_to.at(2) - 1);
        for (int i = 0; i < num_from_to.at(0); i++) {
            char to_move = source.top();
            source.pop();
            target.push(to_move);
        }
    }
    string result;
    for (stack<char> stack : stacks) {
        result += stack.top();
    }
    return result;
}

string day05b(vector<stack<char>>& stacks, const vector<string>& moves) {
    for (const string& move : moves) {
        auto num_from_to = find_numbers<vector<int>>(move);
        stack<char>& source = stacks.at(num_from_to.at(1) - 1);
        stack<char>& target = stacks.at(num_from_to.at(2) - 1);
        deque<char> to_move = {};
        for (int i = 0; i < num_from_to.at(0); i++) {
            to_move.push_front(source.top());
            source.pop();
        }
        for (char ch : to_move) {
            target.push(ch);
        }
    }
    string result;
    for (stack<char> stack : stacks) {
        result += stack.top();
    }
    return result;
}