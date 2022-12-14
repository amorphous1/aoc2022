#include <algorithm>
#include <deque>
#include <string>
#include <vector>
#include "common.h"

using namespace std;

struct Monkey {
    deque<ulong> items_to_inspect;
    string worry_updater;
    int worry_test, worry_test_true_target, worry_test_false_target;
    ulong inspected_items = 0;

    ulong inspect_next_item() {
        ulong old_worry = items_to_inspect.front();
        items_to_inspect.pop_front();
        inspected_items++;
        auto operands = find_numbers<vector<ulong>>(worry_updater);
        ulong operand = (operands.size() == 1) ? operands[0] : old_worry;
        return worry_updater[0] == '*' ? old_worry * operand : old_worry + operand;
    }

    static Monkey parse(const vector<string>& monkey_spec, int start) {
        auto items = find_numbers<deque<ulong>>(monkey_spec[start + 1]);
        string worry_updater = split(monkey_spec[start+2], " new = old ")[1];
        return { items, worry_updater, find_number(monkey_spec[start+3]),
                 find_number(monkey_spec[start+4]), find_number(monkey_spec[start+5]) };
    }
    static bool by_inspected_items_desc(const Monkey& a, const Monkey& b)
    {
        return a.inspected_items > b.inspected_items;
    }
};

ulong day11(const vector<string>& monkey_specs, int rounds, bool divide_worry) {
    vector<Monkey> monkeys;
    ulong multiplied_worry_tests = 1;
    for (int row = 0; row <= monkey_specs.size() - 6; row += 7) {
        const Monkey& monkey = Monkey::parse(monkey_specs, row);
        monkeys.push_back(monkey);
        multiplied_worry_tests *= monkey.worry_test;
    }
    for (int round = 1; round <= rounds; round++) {
        for (Monkey& monkey : monkeys) {
            while (!monkey.items_to_inspect.empty()) {
                ulong updated_worry = monkey.inspect_next_item();
                ulong new_worry = divide_worry ? updated_worry / 3 : updated_worry % multiplied_worry_tests;
                int target = new_worry % monkey.worry_test == 0 ? monkey.worry_test_true_target : monkey.worry_test_false_target;
                monkeys[target].items_to_inspect.push_back(new_worry);
            }
        }
    }
    sort(monkeys.begin(), monkeys.end(), Monkey::by_inspected_items_desc);
    return monkeys[0].inspected_items * monkeys[1].inspected_items;
}

ulong day11a(const vector<string>& monkey_specs) {
    return day11(monkey_specs, 20, true);
}

ulong day11b(const vector<string>& monkey_specs) {
    return day11(monkey_specs, 10000, false);
}