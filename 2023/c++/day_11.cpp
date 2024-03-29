// https://adventofcode.com/2023/day/11

#include "common.hpp"

#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using std::ifstream;
using std::string;
using std::vector;

const char GALAXY = '#', DOT = '.';

typedef struct Galaxy {
  int x, y;
  vector<long> distances;

  long get_distance(const Galaxy &to) const {
    return std::abs(y - to.y) + std::abs(x - to.x);
  }
} Galaxy;

static int no_to_expand(int pos, vector<int> expandable) {
  return std::accumulate(
      expandable.begin(), expandable.end(), 0,
      [pos](int acc, int it_pos) { return it_pos < pos ? acc + 1 : acc; });
}

static vector<Galaxy> find_galaxies(const vector<string> &lines,
                                    int expand_to) {
  vector<Galaxy> galaxies;
  expand_to--;

  vector<int> cols_to_expand;
  for (int col = 0; col < lines[0].length(); ++col) {
    bool should_expand = true;
    for (int row = 0; row < lines.size(); ++row) {
      if (lines[row][col] != DOT) {
        should_expand = false;
        break;
      }
    }

    if (should_expand) {
      cols_to_expand.push_back(col);
    }
  }

  vector<int> rows_to_expand;
  for (int row = 0; row < lines.size(); ++row) {
    if (lines[row].find(GALAXY) == string::npos) {
      rows_to_expand.push_back(row);
    }
  }

  for (int row = 0; row < lines.size(); ++row) {
    for (int col = 0; col < lines[row].length(); ++col) {
      if (lines[row][col] == GALAXY) {
        int rows_above = no_to_expand(row, rows_to_expand);
        int cols_before = no_to_expand(col, cols_to_expand);

        galaxies.push_back(Galaxy{row + expand_to * rows_above,
                                  col + expand_to * cols_before});
      }
    }
  }

  return galaxies;
}

static void find_distances(vector<Galaxy> *galaxies) {
  for (size_t start_g = 0; start_g < galaxies->size(); ++start_g) {
    for (size_t end_g = start_g + 1; end_g < galaxies->size(); ++end_g) {
      galaxies->at(start_g).distances.push_back(
          galaxies->at(start_g).get_distance(galaxies->at(end_g)));
    }
  }
}

static long solve(vector<string> &lines, int expand_to) {
  vector<Galaxy> galaxies = find_galaxies(lines, expand_to);
  find_distances(&galaxies);

  return std::accumulate(galaxies.begin(), galaxies.end(), long(0),
                         [](long acc, const Galaxy &g) {
                           return acc + accumulate(g.distances.begin(),
                                                   g.distances.end(), long(0));
                         });
}

static long part_1(ifstream &input) {
  vector<string> lines = get_lines(input);
  return solve(lines, 2);
}

static long part_2(ifstream &input) {
  vector<string> lines = get_lines(input);
  return solve(lines, 1000000);
}

int main() {
  ifstream input("../input/day_11.txt");

  if (!input.is_open()) {
    perror("ERROR");
    return -1;
  }

  std::cout << part_1(input) << std::endl;
  input.clear();
  input.seekg(ifstream::beg);
  std::cout << part_2(input) << std::endl;

  return 0;
}
