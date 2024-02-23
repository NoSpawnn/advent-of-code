// https://adventofcode.com/2023/day/10

#include "common.hpp"

#include <array>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

enum Pipe {
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
} Pos;

static Pos find_start(const vector<string> &lines) {
  for (size_t row = 0; row < lines.size(); ++row) {
    size_t col;
    if ((col = lines[row].find(Pipe::START)) != string::npos) {
      return Pos{row, col};
    }
  }

  std::cerr << "Start character ('" << char(Pipe::START) << "') not found"
            << std::endl;
  std::exit(EXIT_FAILURE);
}

static int m(size_t start_row, size_t start_col, const vector<string> &lines,
             int cur_len = 0) {
  if (lines[start_row - 1][start_col] == Pipe::NS ||
      lines[start_row - 1][start_col] == Pipe::SW ||
      lines[start_row - 1][start_col] == Pipe::SE) {
    return m(start_row - 1, start_col, lines, cur_len + 1);
  }
  if (lines[start_col + 1][start_col] == Pipe::NS ||
      lines[start_col + 1][start_col] == Pipe::NW ||
      lines[start_col + 1][start_col] == Pipe::NE) {
    return m(start_row + 1, start_col, lines, cur_len + 1);
  }
  if (lines[start_col][start_col + 1] == Pipe::EW ||
      lines[start_col][start_col + 1] == Pipe::NW ||
      lines[start_col][start_col + 1] == Pipe::SW) {
    return m(start_row, start_col + 1, lines, cur_len + 1);
  }
  if (lines[start_col][start_col - 1] == Pipe::EW ||
      lines[start_col][start_col - 1] == Pipe::NE ||
      lines[start_col][start_col - 1] == Pipe::SE) {
    return m(start_row, start_col - 1, lines, cur_len + 1);
  }

  return cur_len;
}

long part_1(ifstream &input) {
  vector<string> lines = get_lines(input);
  Pos start = find_start(lines);

  return m(start.row, start.col, lines, 'N');
}

int main() {
  ifstream input("../input/day_10.txt");

  if (!input.is_open()) {
    perror("ERROR");
    return EXIT_FAILURE;
  }

  std::cout << part_1(input) << std::endl;
  // input.clear();
  // input.seekg(ifstream::beg);
  // std::cout << part_2(input) << std::endl;

  return EXIT_SUCCESS;
}
