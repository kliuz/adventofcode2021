#include <fstream>
#include <functional>
#include <iostream>
#include <unordered_map>

using namespace std;

void update_or_insert_counts(unordered_map<int, int>& counts, int key, int update) {
    if (counts.count(key) > 0) {
        int updated_count = counts.find(key)->second + update;
        counts[key] = updated_count;
    } else {
        counts.insert({key, 1});
    }
}

int compute_decimal_value(unordered_map<int, int>& counts, function<bool(int)> comparator) {
    int value = 0;
    for (int i = 0; i < counts.size(); i++) {
        int count = counts.find(i)->second;
        value <<= 1;
        if (comparator(count)) {
            value |= 1;
        }
    }
    return value;
}

int part1(ifstream&& ifs) {
    if (!ifs) {
        cerr << "Couldn't open input file" << endl;
    }

    string line;
    char* token;
    unordered_map<int, int> counts;
    while (getline(ifs, line)) {
        const char* line_arr = line.c_str();
        for (int i = 0; i < line.length(); i++) {
            if (line_arr[i] == '0') {
                update_or_insert_counts(counts, i, -1);
            } else {
                update_or_insert_counts(counts, i, 1);
            }
        }
    }

    int gamma = compute_decimal_value(counts, [](int count){ return count > 0; });
    int epsilon = compute_decimal_value(counts, [](int count){ return count < 0; });
    return gamma * epsilon;
}

int main() {
    string filename = "input.txt";
    ifstream&& ifs {filename};

    cout << "Answer: " << part1(ifstream(filename)) << endl;
}
