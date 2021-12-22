#include <fstream>
#include <iostream>

using namespace std;

int main() {
    string filename = "input.txt";
    ifstream ifs {filename};

    if (!ifs) {
        cerr << "Couldn't open input file " << filename << endl;
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
    cout << "Number of increases: " << num_increases << endl;
}
