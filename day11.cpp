#include <algorithm>
#include <deque>
#include <string>
#include <vector>
#include "common.h"
#include "tinyexpr.h"

using namespace std;

struct Monkey {
    deque<int> items_to_inspect;
    string worry_updater;
    int worry_test, worry_test_true_target, worry_test_false_target;
    int inspected_items = 0;

    static Monkey parse(const vector<string>& monkey_spec, int start) {
        auto items = find_numbers<deque<int>>(monkey_spec[start + 1]);
        string worry_updater = split(monkey_spec[start+2], " = ")[1];
        return { items, worry_updater, find_number(monkey_spec[start+3]),
                 find_number(monkey_spec[start+4]), find_number(monkey_spec[start+5]) };
    }
    static bool by_inspected_items_desc(const Monkey& a, const Monkey& b)
    {
        return a.inspected_items > b.inspected_items;
    }
};

int day11a(const vector<string>& monkey_specs) {
    vector<Monkey> monkeys;
    for (int row = 0; row <= monkey_specs.size() - 6; row += 7) {
        monkeys.push_back(Monkey::parse(monkey_specs, row));
    }
    for (Monkey m : monkeys) {
        cout << m.items_to_inspect[0] << " " << m.worry_updater << " " << m.worry_test << " " << m.worry_test_true_target << " " << m.worry_test_false_target << endl;
    }
    for (int round = 1; round <= 20; round++) {
        for (Monkey& monkey : monkeys) {
            while (!monkey.items_to_inspect.empty()) {
                double old_worry = monkey.items_to_inspect.front();
                monkey.items_to_inspect.pop_front();
                monkey.inspected_items++;
                te_variable vars[] = { {"old", &old_worry} };
                double updated_worry = te_eval(te_compile(monkey.worry_updater.c_str(), vars, 1, nullptr));
                int new_worry = int(updated_worry) / 3;
                int target = new_worry % monkey.worry_test == 0 ? monkey.worry_test_true_target : monkey.worry_test_false_target;
                monkeys[target].items_to_inspect.push_back(new_worry);
            }
        }
    }
    sort(monkeys.begin(), monkeys.end(), Monkey::by_inspected_items_desc);
    for (const Monkey& monkey : monkeys) {
        cout << "items inspected: " << monkey.inspected_items << endl;
        for (int item : monkey.items_to_inspect) {
            cout << item << " ";
        }
        cout << endl;
    }
    return monkeys[0].inspected_items * monkeys[1].inspected_items;
}
