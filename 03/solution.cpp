#include <algorithm>
#include <bitset>
#include <fstream>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

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

string compute_part_2_ratings(vector<string>& numbers, function<bool(int, int)> comparator) {
    int i = 0;
    vector<string>::iterator lo = numbers.begin();
    vector<string>::iterator hi = numbers.end();
    while (lo < (hi - 1)) {
        int count = 0;
        auto curr = lo;
        for (; curr < hi; curr++) {
           // cout << "iteration " << i << ": " << *curr << endl;
           if ((*curr).at(i) != '0') {
               break;
           }
           count++;
        }

        int half = (hi - lo) / 2;
        // cout << "count: " << count << " half: " << half << " curr: " << (curr - lo) << endl;
        if (comparator(count, half)) {
            // cout << "if statement evaluated to true" << endl;
            lo = curr;
        } else {
            // cout << "else statement evaluated to true" << endl;
            hi = curr;
        }
        i++;
    }
    return *lo;
}

int part1(ifstream&& ifs) {
    if (!ifs) {
        cerr << "Couldn't open input file" << endl;
    }

    string line;
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

int part2(ifstream&& ifs) {
    if (!ifs) {
        cerr << "Couldn't open input file" << endl;
    }

    string line;
    vector<string> numbers;
    while (getline(ifs, line)) {
        numbers.push_back(line);
    }
    sort(numbers.begin(), numbers.end());

    string oxygen = compute_part_2_ratings(numbers, [](int count, int half) { return count <= half; });
    string co2 = compute_part_2_ratings(numbers, [](int count, int half) { return count > half; });

    cout << "Oxygen " << oxygen << " CO2 " << co2 << endl;
    return stoi(oxygen, nullptr, 2) * stoi(co2, nullptr, 2);
}

int main() {
    string filename = "input.txt";
    ifstream&& ifs {filename};

    int part1_answer = part1(ifstream(filename));
    cout << "Answer: " << part1_answer << endl;
    int part2_answer = part2(ifstream(filename));
    cout << "Answer: " << part2_answer << endl;
}
