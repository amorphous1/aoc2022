#include <deque>
#include <string>
#include <vector>
#include <iostream>
#include "common.h"

using namespace std;

struct Packet {
    static constexpr int LIST_START = -1, LIST_END = -2;
    deque<int> tokens;

    static Packet parse(const string& s) {
        deque<int> tokens;
        string current_number;
        for (char ch : s) {
            if (ch >= '0' && ch <= '9')
                current_number += ch;
            else if (!current_number.empty()) {
                tokens.push_back(stoi(current_number));
                current_number = "";
            }
            if (ch == '[') tokens.push_back(LIST_START);
            if (ch == ']') tokens.push_back(LIST_END);
        }
        return { tokens };
    }

    friend ostream& operator<<(ostream& o, const Packet& p)
    {
        string text;
        for (const int& token : p.tokens) {
                text += to_string(token) + " ";
        }
        return o << text;
    }
};

int compare(const Packet& packet1, const Packet& packet2) { // return -1/0/1 if packet1 is smaller/equal/bigger than packet2
    deque<int> p1(packet1.tokens), p2(packet2.tokens);
    while (!p1.empty() && !p2.empty()) {
        int t1 = p1.front();
        p1.pop_front();
        int t2 = p2.front();
        p2.pop_front();
        if (t1 == t2) continue;
        if (t1 == Packet::LIST_END) return -1;  // packet1 smaller since a list in packet1 is shorter
        if (t2 == Packet::LIST_END) return 1;   // packet2 bigger since a list in packet2 is shorter
        if (t1 == Packet::LIST_START) {         // "package up" packet2's integer in a list
            p2.push_front(Packet::LIST_END);
            p2.push_front(t2);
        } else if (t2 == Packet::LIST_START) {  // "package up" packet1's integer in a list
            p1.push_front(Packet::LIST_END);
            p1.push_front(t1);
        } else
            return sgn(t1 - t2);                // at this point, both tokens must be different integers
    }
    if (!p1.empty()) return 1;                  // packet1 is bigger, because it contains more tokens
    if (!p2.empty()) return -1;                 // packet1 is smaller, because it contains fewer tokens
    return 0;
}

int day13a(const vector<string>& lines) {
    vector<pair<Packet, Packet>> packet_pairs;
    for (int row = 0; row < lines.size(); row += 3) {
        packet_pairs.push_back(make_pair(Packet::parse(lines[row]), Packet::parse(lines[row+1])));
    }
    int result = 0;
    for (int i = 0; i < packet_pairs.size(); i++) {
        cout << packet_pairs[i].first << endl << packet_pairs[i].second << endl;
        cout << compare(packet_pairs[i].first, packet_pairs[i].second) << endl << endl;
        result += compare(packet_pairs[i].first, packet_pairs[i].second) < 0 ? i + 1 : 0;
    }
    return result;
}