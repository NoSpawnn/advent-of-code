// https://adventofcode.com/2023/day/10

#include "common.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Tile {
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
  Tile type;
} Pos;

struct Direction {
  int row_os, col_os;
} N{-1, 0}, S{1, 0}, E{0, 1}, W{0, -1};

static Pos find_start(const vector<string> &lines) {
  for (size_t row = 0; row < lines.size(); ++row) {
    size_t col;
    if ((col = lines[row].find(Tile::START)) != string::npos) {
      return Pos{row, col};
    }
  }

  std::cerr << "Start character ('" << char(Tile::START) << "') not found"
            << std::endl;
  exit(EXIT_FAILURE);
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
    perror("ERROR");
    return EXIT_FAILURE;
  }

  std::cout << part_1(input) << std::endl;
  // input.clear();
  // input.seekg(ifstream::beg);
  // std::cout << part_2(input) << std::endl;

  return EXIT_SUCCESS;
}
