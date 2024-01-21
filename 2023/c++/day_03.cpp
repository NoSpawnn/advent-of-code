// https://adventofcode.com/2023/day/3

#include "common.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

const char DOT = '.';
const char STAR = '*';

typedef struct Punct {
  int line;
  int col;
} Punct;

typedef struct Digit {
  int line;
  int start;
  int end;
} Digit;

vector<Digit> find_digits(const vector<string> &lines) {
  vector<Digit> digits;

  for (int line = 0; line < lines.size(); ++line) {
    for (int col = 0; col < lines[line].size(); ++col) {
      if (std::isdigit(lines[line][col])) {
        int start = col, end = col + 1;

        while (end <= lines[line].size() && std::isdigit(lines[line][end])) {
          end++;
        }

        digits.push_back(Digit{line, start, end});
        col = end;
      }
    }
  }

  return digits;
}

vector<Punct> find_puncts(const vector<string> &lines) {
  vector<Punct> puncts;

  for (int line = 0; line < lines.size(); ++line) {
    for (int col = 0; col < lines[line].size(); ++col) {
      if (!std::isdigit(lines[line][col]) && lines[line][col] != DOT) {
        puncts.push_back(Punct{line, col});
      }
    }
  }

  return puncts;
}

bool is_in_range(int punct_line, int punct_col, int digit_line, int digit_start,
                 int digit_end) {
  return std::abs(int(punct_line) - int(digit_line)) <= 1 &&
         digit_start - 1 <= punct_col && punct_col <= digit_end;
}

int part_1(ifstream &input) {
  int total = 0;
  vector<string> lines = get_lines(input);
  vector<Digit> digit_positions = find_digits(lines);
  vector<Punct> punct_positions = find_puncts(lines);

  for (Punct p : punct_positions) {
    for (Digit d : digit_positions) {
      if (is_in_range(p.line, p.col, d.line, d.start, d.end)) {
        total += std::stoi(lines[d.line].substr(d.start, d.end - d.start));
      }
    }
  }

  return total;
}

int part_2(ifstream &input) {
  int total = 0;
  vector<string> lines = get_lines(input);
  vector<Digit> digit_positions = find_digits(lines);
  vector<Punct> punct_positions = find_puncts(lines);

  for (Punct p : punct_positions) {
    std::pair<size_t, size_t> matched;

    for (Digit d : digit_positions) {
      if (lines[p.line][p.col] != STAR) {
        continue;
      }

      if (is_in_range(p.line, p.col, d.line, d.start, d.end)) {
        int num = std::stoi(lines[d.line].substr(d.start, d.end - d.start));

        if (matched.first == 0) {
          matched.first = num;
        } else {
          matched.second = num;
        }
      }
    }

    if (matched.first != 0 && matched.second != 0) {
      total += matched.first * matched.second;
    }
  }

  return total;
}

int main() {
  ifstream input("../input/day_03.txt");

  if (!input.is_open()) {
    perror(NULL);
    return -1;
  }

  cout << "PART 1 TOTAL: " << part_1(input) << endl;
  input.clear();
  input.seekg(ifstream::beg);
  cout << "PART 2 TOTAL: " << part_2(input) << endl;

  return 0;
}