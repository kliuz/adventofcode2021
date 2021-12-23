#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

enum Direction { none, forward, up, down };

int part1(ifstream&& ifs) {
    if (!ifs) {
        cerr << "Couldn't open input file for part 1" << endl;
    }

    string line;
    char* token;
    int horizontal = 0;
    int vertical = 0;
    while (getline(ifs, line)) {
        Direction direction = none;
        token = strtok(&line[0], " ");
        while (token != nullptr) {
            if (direction == Direction::none) {
                if (strcmp(token, "forward") == 0) {
                    direction = Direction::forward;
                } else if (strcmp(token, "up") == 0) {
                    direction = Direction::up;
                } else if (strcmp(token, "down") == 0) {
                    direction = Direction::down;
                }
            } else {
                switch (direction) {
                    case Direction::forward:
                        horizontal += (int) strtol(token, nullptr, 10);
                        break;
                    case Direction::up:
                        vertical -= (int) strtol(token, nullptr, 10);
                        break;
                    case Direction::down:
                        vertical += (int) strtol(token, nullptr, 10);
                        break;
                }
            }
            token = strtok(nullptr, " ");
        }
    }
    return horizontal * vertical;
}

int part2(ifstream&& ifs) {
    if (!ifs) {
        cerr << "Couldn't open input file for part 1" << endl;
    }

    string line;
    char* token;
    int horizontal = 0;
    int vertical = 0;
    int aim = 0;
    while (getline(ifs, line)) {
        Direction direction = none;
        token = strtok(&line[0], " ");
        while (token != nullptr) {
            if (direction == Direction::none) {
                if (strcmp(token, "forward") == 0) {
                    direction = Direction::forward;
                } else if (strcmp(token, "up") == 0) {
                    direction = Direction::up;
                } else if (strcmp(token, "down") == 0) {
                    direction = Direction::down;
                }
            } else {
                switch (direction) {
                    case Direction::forward:
                        horizontal += (int) strtol(token, nullptr, 10);
                        vertical += ((int) strtol(token, nullptr, 10)) * aim;
                        break;
                    case Direction::up:
                        aim -= (int) strtol(token, nullptr, 10);
                        break;
                    case Direction::down:
                        aim += (int) strtol(token, nullptr, 10);
                        break;
                }
            }
            token = strtok(nullptr, " ");
        }
    }
    return horizontal * vertical;
}

int main() {
    string filename = "input.txt";
    ifstream&& ifs {filename};

    cout << "Answer: " << part1(ifstream(filename)) << endl;
    cout << "Answer: " << part2(ifstream(filename)) << endl;
}
