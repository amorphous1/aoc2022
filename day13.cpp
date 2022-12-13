#include <algorithm>
#include <deque>
#include <string>
#include <vector>

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
};

bool is_smaller(const Packet& packet1, const Packet& packet2) {  // return true if packet1 is smaller than packet2
    deque<int> tokens1(packet1.tokens), tokens2(packet2.tokens);
    while (!tokens1.empty() && !tokens2.empty()) {
        int t1 = tokens1.front();
        tokens1.pop_front();
        int t2 = tokens2.front();
        tokens2.pop_front();
        if (t1 == t2) continue;
        if (t1 == Packet::LIST_END) return true;   // packet1 is smaller since a list in packet1 ends sooner
        if (t2 == Packet::LIST_END) return false;  // packet1 is bigger since a list in packet2 ends sooner
        if (t1 == Packet::LIST_START) {            // "package up" packet2's integer in a list
            tokens2.push_front(Packet::LIST_END);
            tokens2.push_front(t2);
        } else if (t2 == Packet::LIST_START) {     // "package up" packet1's integer in a list
            tokens1.push_front(Packet::LIST_END);
            tokens1.push_front(t1);
        } else
            return t1 < t2;                        // at this point, both tokens must be different integers
    }
    return tokens1.empty();
}

int day13a(const vector<string>& lines) {
    vector<pair<Packet, Packet>> packet_pairs;
    for (int row = 0; row < lines.size(); row += 3) {
        packet_pairs.push_back(make_pair(Packet::parse(lines[row]), Packet::parse(lines[row+1])));
    }
    int result = 0;
    for (int i = 0; i < packet_pairs.size(); i++) {
        result += is_smaller(packet_pairs[i].first, packet_pairs[i].second) ? i + 1 : 0;
    }
    return result;
}

int day13b(const vector<string>& lines) {
    Packet divider1 = Packet::parse("[[2]]"), divider2 = Packet::parse("[[6]]");
    vector<Packet> packets = { divider1, divider2 };
    for (int row = 0; row < lines.size(); row += 3) {
        packets.push_back(Packet::parse(lines[row]));
        packets.push_back(Packet::parse(lines[row+1]));
    }
    sort(packets.begin(), packets.end(), is_smaller);
    int result = 1;
    for (int i = 0; i < packets.size(); i++) {
        result *= (packets[i].tokens == divider1.tokens || packets[i].tokens == divider2.tokens) ? i + 1 : 1;
    }
    return result;
}