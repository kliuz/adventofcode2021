#include <fstream>
#include <iostream>
#include <string.h>
#include <unordered_map>
#include <vector>

using namespace std;

class Square {
public:
  Square(int num) : number{num}, drawn{false} {}
  Square(int num, bool drawn) : number{num}, drawn{drawn} {}

  int get_num() { return number; }

  bool is_drawn() { return drawn; }

  bool draw() { drawn = true; }

private:
  int number;
  bool drawn;
};

class Board {
public:
  Board(vector<vector<Square>> values) : values{values} {
    for (int i = 0; i < values.size(); i++) {
      for (int j = 0; j < values.at(i).size(); j++) {
        Square square = values.at(i).at(j);
        value_to_indices.insert({square.get_num(), pair<int, int>(i, j)});
      }
    }
  }

  void draw_number(int num) {
    if (value_to_indices.count(num) == 0) {
      return;
    }
    auto &indices = value_to_indices.at(num);
    values.at(indices.first).at(indices.second).draw();
  }

  vector<vector<Square>> get_squares() { return values; }

  bool check_bingo() {
    bool found_bingo;

    // Check rows
    for (int i = 0; i < values.size(); i++) {
      found_bingo = true;
      for (int j = 0; j < values.at(i).size(); j++) {
        if (!values.at(i).at(j).is_drawn()) {
          found_bingo = false;
          break;
        }
      }
      if (found_bingo) {
        return true;
      }
    }

    // Check columns
    for (int j = 0; j < values.size(); j++) {
      found_bingo = true;
      for (int i = 0; i < values.at(j).size(); i++) {
        if (!values.at(i).at(j).is_drawn()) {
          found_bingo = false;
          break;
        }
      }
      if (found_bingo) {
        return true;
      }
    }

    // Check diagonals
    found_bingo = true;
    for (int i = 0; i < values.size(); i++) {
      if (!values.at(i).at(i).is_drawn()) {
        found_bingo = false;
        break;
      }
    }
    if (found_bingo) {
      return true;
    }
    found_bingo = true;
    for (int i = 0; i < values.size(); i++) {
      if (!values.at(values.size() - 1 - i).at(i).is_drawn()) {
        found_bingo = false;
        break;
      }
    }
    if (found_bingo) {
      return true;
    }

    return false;
  }

private:
  vector<vector<Square>> values;
  unordered_map<int, pair<int, int>> value_to_indices;
};

bool isalnum(string str) {
  int i = 0;

  while (i < str.length()) {
    if (std::isalnum(str[i])) {
      return true;
    }
    ++i;
  }
  return false;
}

vector<Board> parse_boards(ifstream &&ifs, string &line) {
  vector<Board> boards;
  vector<vector<Square>> values;
  int row = 0;
  while (getline(ifs, line)) {
    if (!isalnum(line)) {
      if (values.size() > 0) {
        boards.push_back(Board(values));
        values.clear();
      }
      row = 0;
      continue;
    }
    char *num = strtok(&line[0], " ");
    vector<Square> row_squares;
    while (num != nullptr) {
      row_squares.push_back(Square(stoi(num, nullptr, 10)));
      num = strtok(nullptr, " ");
    }
    values.push_back(row_squares);
    row++;
  }
  return boards;
}

void draw_num_for_all_boards(vector<Board> &boards, int num) {
  for (auto &board : boards) {
    board.draw_number(num);
  }
}

int check_bingo_for_all_boards(vector<Board> &boards) {
  for (auto &board : boards) {
    if (board.check_bingo()) {
      vector<vector<Square>> squares = board.get_squares();
      int sum_unmarked = 0;
      for (auto &square_row : squares) {
        for (auto &square : square_row) {
          if (!square.is_drawn()) {
            sum_unmarked += square.get_num();
          }
        }
      }
      return sum_unmarked;
    }
  }
  return -1;
}

void check_bingo_for_all_boards(vector<Board> &boards,
                                unordered_map<int, int> &winning_boards,
                                int num) {
  for (int i = 0; i < boards.size(); i++) {
    auto &board = boards.at(i);
    if (winning_boards.count(i) == 0 && board.check_bingo()) {
      vector<vector<Square>> squares = board.get_squares();
      int sum_unmarked = 0;
      for (auto &square_row : squares) {
        for (auto &square : square_row) {
          if (!square.is_drawn()) {
            sum_unmarked += square.get_num();
          }
        }
      }
      cout << i << " " << (sum_unmarked * num) << endl;
      winning_boards.insert({i, sum_unmarked});
    }
  }
}

int part1(ifstream &&ifs) {
  if (!ifs) {
    cerr << "Couldn't open input file" << endl;
  }

  string line;

  // Parse first line to get the numbers drawn
  getline(ifs, line);

  char *token;
  vector<int> numbers_drawn;
  token = strtok(&line[0], ",");
  while (token != nullptr) {
    numbers_drawn.push_back(stoi(token, nullptr, 10));
    token = strtok(nullptr, ",");
  }

  vector<Board> boards = parse_boards(move(ifs), line);

  for (auto num : numbers_drawn) {
    draw_num_for_all_boards(boards, num);
    int result = check_bingo_for_all_boards(boards);
    if (result > 0) {
      return result * num;
    }
  }
}

void part2(ifstream &&ifs) {
  if (!ifs) {
    cerr << "Couldn't open input file" << endl;
  }

  string line;

  // Parse first line to get the numbers drawn
  getline(ifs, line);

  char *token;
  vector<int> numbers_drawn;
  token = strtok(&line[0], ",");
  while (token != nullptr) {
    numbers_drawn.push_back(stoi(token, nullptr, 10));
    token = strtok(nullptr, ",");
  }

  unordered_map<int, int> winning_boards;
  vector<Board> boards = parse_boards(move(ifs), line);

  for (auto num : numbers_drawn) {
    draw_num_for_all_boards(boards, num);
    check_bingo_for_all_boards(boards, winning_boards, num);
    //    cout << result * num << endl;;
  }
}

int main() {
  string filename = "input.txt";

  int part1_answer = part1(ifstream(filename));
  cout << "Answer: " << part1_answer << endl;
  part2(ifstream(filename));
}
