#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int part1(ifstream&& ifs) {
    if (!ifs) {
        cerr << "Couldn't open input file for part 1" << endl;
    }

    string line;
    int curr = -1;
    int num_increases = 0;
    while (getline(ifs, line)) {
        int val = stoi(line);
        if (curr == -1) {
            curr = val;
            continue;
        }
        if (val > curr) {
            num_increases++;
        }
        curr = val;
    }
    return num_increases;
}

int part2(ifstream&& ifs, int window_size) {
    if (!ifs) {
        cerr << "Couldn't open input file for part 1" << endl;
    }

    string line;
    vector<int> window;
    int num_increases = 0;
    while (getline(ifs, line)) {
        int val = stoi(line);
        if (window.size() < window_size) {
            window.push_back(val);
            continue;
        }
        vector<int>::iterator it = window.begin();
        if (val > *it) {
            num_increases++;
        }

        window.push_back(val);
        window.erase(window.begin());
    }
    return num_increases;
}


int main() {
    string filename = "input.txt";
    ifstream&& ifs {filename};

    cout << "Number of increases: " << part1(ifstream(filename)) << endl;
    cout << "Number of increases: " << part2(ifstream(filename), 3) << endl;
}
