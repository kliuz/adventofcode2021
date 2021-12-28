#include <fstream>
#include <iostream>
#include <string.h>
#include <unordered_map>
#include <vector>

using namespace std;

long part1(vector<int> &initial_fishes, int days) {
  unordered_map<int, long> days_to_fish = {
      {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}};
  for (auto fish : initial_fishes) {
    long &num_fish = days_to_fish.at(fish);
    num_fish += 1;
  }

  for (int i = 0; i < days; i++) {
    long fishes_born = days_to_fish.at(0);
    for (int k = 0; k < (days_to_fish.size() - 1); k++) {
      long young = days_to_fish.at(k + 1);
      long &old = days_to_fish.at(k);
      old = young;
    }
    long &reset = days_to_fish.at(6);
    reset += fishes_born;
    long &newborns = days_to_fish.at(8);
    newborns = fishes_born;
  }

  long total_fishes = 0;
  for (auto &entry : days_to_fish) {
    total_fishes += entry.second;
  }
  return total_fishes;
}

long part2(vector<int> &initial_fishes, int days) {
  return part1(initial_fishes, days);
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
  vector<int> initial_fishes;
  while (token != nullptr) {
    initial_fishes.push_back(stoi(token, nullptr, 10));
    token = strtok(nullptr, ",");
  }

  long part1_answer = part1(initial_fishes, 80);
  cout << "Answer: " << part1_answer << endl;
  long part2_answer = part2(initial_fishes, 256);
  cout << "Answer: " << part2_answer << endl;
}
