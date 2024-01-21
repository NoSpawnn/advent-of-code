// https://adventofcode.com/2023/day/10

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Conn {
  START = 'S',
  GROUND = '.',
  NS = '|',
  EW = '-',
  NE = 'L',
  NW = 'J',
  SW = '7',
  SE = 'F',
};

typedef struct Path {
  long length, distance;
} Path;

typedef struct Pos {
  size_t row, col;
  Conn type;
} Pos;

struct Direction {
  int row_os, col_os;
} N{-1, 0}, S{1, 0}, E{0, 1}, W{0, -1};

static vector<string> get_lines(ifstream &file) {
  vector<string> lines;
  string line;

  while (getline(file, line)) {
    lines.push_back(line);
  }

  return lines;
}

static Pos find_start(const vector<string> &lines) {
  Pos start_pos = Pos{0, 0};

  for (size_t row = 0; row < lines.size(); ++row) {
    for (size_t col = 0; col < lines[row].length(); ++col) {
      if (lines[row][col] == Conn::START) {
        start_pos.row = row;
        start_pos.col = col;

        return start_pos;
      }
    }
  }

  // just to avoid compiler complaint about not returning a value in all
  // cases, we know for sure there will be exactly one matching character
  // somewhere
  return start_pos;
}

static Path do_move(const vector<string> &lines, const Pos p,
                        const Direction d) {
  Path path;

  if (lines[p.row + d.row_os][p.col + d.col_os]) {
  }

  return path;
}

long part_1(ifstream &input) {
  long longest_distance = 0;
  vector<string> lines = get_lines(input);
  Pos start_pos = find_start(lines);
  Pos current_pos = start_pos;

  return longest_distance;
}

int main() {
  ifstream input("../input/day_10.txt");

  if (!input.is_open()) {
    perror(NULL);
    return -1;
  }

  std::cout << part_1(input) << std::endl;
  // input.clear();
  // input.seekg(ifstream::beg);
  // std::cout << part_2(input) << std::endl;

  return 0;
}