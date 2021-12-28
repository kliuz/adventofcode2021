#include <boost/functional/hash.hpp>
#include <fstream>
#include <iostream>
#include <string.h>
#include <unordered_map>
#include <vector>

using namespace std;

pair<int, int> get_coord(char *coord) {
  char *token = strtok(coord, ",");
  int first = stoi(token, nullptr, 10);
  token = strtok(nullptr, ",");
  int second = stoi(token, nullptr, 10);

  return make_pair(first, second);
}

void insert_or_update(
    unordered_map<pair<int, int>, int, boost::hash<pair<int, int>>>
        &coord_to_lines,
    pair<int, int> coord) {
  if (coord_to_lines.count(coord) == 0) {
    coord_to_lines.insert({coord, 1});
  } else {
    int &num_intersections = coord_to_lines.at(coord);
    num_intersections += 1;
  }
}

int part1(ifstream &&ifs) {
  if (!ifs) {
    cerr << "Couldn't open input file" << endl;
  }

  unordered_map<pair<int, int>, int, boost::hash<pair<int, int>>>
      coord_to_lines;
  string line;
  while (getline(ifs, line)) {
    char *first_pair = strtok(&line[0], " ");
    strtok(nullptr, " "); // Skip "->" token
    char *second_pair = strtok(nullptr, " ");

    pair<int, int> start = get_coord(first_pair);
    pair<int, int> end = get_coord(second_pair);

    if (start.first == end.first) {
      int lo = start.second < end.second ? start.second : end.second;
      int hi = start.second > end.second ? start.second : end.second;
      for (int i = lo; i <= hi; i++) {
        insert_or_update(coord_to_lines, make_pair(start.first, i));
      }
    } else if (start.second == end.second) {
      int lo = start.first < end.first ? start.first : end.first;
      int hi = start.first > end.first ? start.first : end.first;
      for (int i = lo; i <= hi; i++) {
        insert_or_update(coord_to_lines, make_pair(i, start.second));
      }
    }
  }

  int count = 0;
  for (auto &entry : coord_to_lines) {
    if (entry.second >= 2) {
      count++;
    }
  }

  return count;
}

int part2(ifstream &&ifs) {
  if (!ifs) {
    cerr << "Couldn't open input file" << endl;
  }

  unordered_map<pair<int, int>, int, boost::hash<pair<int, int>>>
      coord_to_lines;
  string line;
  while (getline(ifs, line)) {
    char *first_pair = strtok(&line[0], " ");
    strtok(nullptr, " "); // Skip "->" token
    char *second_pair = strtok(nullptr, " ");

    pair<int, int> start = get_coord(first_pair);
    pair<int, int> end = get_coord(second_pair);

    if (start.first == end.first) {
      int lo = start.second < end.second ? start.second : end.second;
      int hi = start.second > end.second ? start.second : end.second;
      for (int i = lo; i <= hi; i++) {
        insert_or_update(coord_to_lines, make_pair(start.first, i));
      }
    } else if (start.second == end.second) {
      int lo = start.first < end.first ? start.first : end.first;
      int hi = start.first > end.first ? start.first : end.first;
      for (int i = lo; i <= hi; i++) {
        insert_or_update(coord_to_lines, make_pair(i, start.second));
      }
    } else if (start.first > end.first && start.second > end.second) {
      for (int i = start.first, j = start.second;
           i >= end.first && j >= end.second; i--, j--) {
        insert_or_update(coord_to_lines, make_pair(i, j));
      }
    } else if (start.first > end.first && start.second < end.second) {
      for (int i = start.first, j = start.second;
           i >= end.first && j <= end.second; i--, j++) {
        insert_or_update(coord_to_lines, make_pair(i, j));
      }
    } else if (start.first < end.first && start.second > end.second) {
      for (int i = start.first, j = start.second;
           i <= end.first && j >= end.second; i++, j--) {
        insert_or_update(coord_to_lines, make_pair(i, j));
      }
    } else if (start.first < end.first && start.second < end.second) {
      for (int i = start.first, j = start.second;
           i <= end.first && j <= end.second; i++, j++) {
        insert_or_update(coord_to_lines, make_pair(i, j));
      }
    }
  }

  int count = 0;
  for (auto &entry : coord_to_lines) {
    if (entry.second >= 2) {
      count++;
    }
  }

  return count;
}

int main() {
  string filename = "input.txt";

  int part1_answer = part1(ifstream(filename));
  cout << "Answer: " << part1_answer << endl;
  int part2_answer = part2(ifstream(filename));
  cout << "Answer: " << part2_answer << endl;
}
