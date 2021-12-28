#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <string.h>

using namespace std;

int part1(map<int, int> position_to_count) {
  int lo = position_to_count.begin()->first;
  int hi = position_to_count.rbegin()->first;

  int min_fuel = numeric_limits<int>::max();
  for (int i = lo; i <= hi; i++) {
    int fuel_consumed = 0;
    for (auto &entry : position_to_count) {
      fuel_consumed += abs(entry.first - i) * entry.second;
    }
    if (fuel_consumed < min_fuel) {
      min_fuel = fuel_consumed;
    }
  }
  return min_fuel;
}

int cost(int distance) { return (distance * (distance + 1)) / 2; }

int part2(map<int, int> position_to_count) {
  int lo = position_to_count.begin()->first;
  int hi = position_to_count.rbegin()->first;

  int min_fuel = numeric_limits<int>::max();
  for (int i = lo; i <= hi; i++) {
    int fuel_consumed = 0;
    for (auto &entry : position_to_count) {
      fuel_consumed += cost(abs(entry.first - i)) * entry.second;
    }
    if (fuel_consumed < min_fuel) {
      min_fuel = fuel_consumed;
    }
  }
  return min_fuel;
}

int main() {
  string filename = "input.txt";
  ifstream ifs(filename);
  if (!ifs) {
    cerr << "Couldn't open input file" << endl;
  }

  string line;
  getline(ifs, line);
  char *token = strtok(&line[0], ",");
  map<int, int> position_to_count;
  while (token != nullptr) {
    int coord = stoi(token, nullptr, 10);
    if (position_to_count.count(coord) == 0) {
      position_to_count.insert({coord, 1});
    } else {
      int &position = position_to_count.at(coord);
      position += 1;
    }
    token = strtok(nullptr, ",");
  }

  int part1_answer = part1(position_to_count);
  cout << "Answer: " << part1_answer << endl;
  int part2_answer = part2(position_to_count);
  cout << "Answer: " << part2_answer << endl;
}
