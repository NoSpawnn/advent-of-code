// https://adventofcode.com/2023/day/10

#include "common.hpp"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <utility>

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

enum Direction {
  N = 'N',
  S = 'S',
  E = 'E',
  W = 'W',
};

typedef struct Path {
  long length, distance;
} Path;

Pipe pipe_from_char(const char c) {
  switch (c) {
  case 'S':
    return START;
  case '.':
    return GROUND;
  case '|':
    return NS;
  case '-':
    return EW;
  case 'L':
    return NE;
  case 'J':
    return NW;
  case '7':
    return SW;
  case 'F':
    return SE;
  }

  std::cout << c << " NOT FOUND IN TILES" << std::endl;
  exit(EXIT_FAILURE);
}

static pair<size_t, size_t> find_start(const vector<string> &lines) {
  for (size_t row = 0; row < lines.size(); ++row) {
    size_t col;
    if ((col = lines[row].find(Pipe::START)) != string::npos) {
      return make_pair(row, col);
    }
  }

  std::cerr << "Start character ('" << char(Pipe::START) << "') not found"
            << std::endl;
  std::exit(EXIT_FAILURE);
}

static void add_direction(stack<Direction> &directions, Pipe pipe,
                          Direction from) {
  switch (pipe) {
  case START:
    break;
  case NS:
    directions.push(from == N ? S : N);
    break;
  case EW:
    directions.push(from == E ? W : E);
    break;
  case NE:
    directions.push(from == N ? E : N);
    break;
  case NW:
    directions.push(from == N ? W : N);
    break;
  case SW:
    directions.push(from == S ? W : S);
    break;
  case SE:
    directions.push(from == S ? E : S);
    break;
  default:
    std::cout << "BAD PIPE" << std::endl;
    exit(EXIT_FAILURE);
  }
}

int part_1(ifstream &input) {
  vector<string> lines = get_lines(input);
  pair<size_t, size_t> start = find_start(lines);
  pair<size_t, size_t> current_pos = start;
  stack<Direction> directions;
  directions.push(E);
  map<Direction, int> path_lengths = {
      {N, 0},
      {S, 0},
      {E, 0},
      {W, 0},
  };

  while (!directions.empty()) {
    switch (directions.top()) {
      directions.pop();
    case N:
      path_lengths[N] += (lines[current_pos.first][current_pos.second] == NS ||
                          lines[current_pos.first][current_pos.second] == SW ||
                          lines[current_pos.first][current_pos.second] == SE)
                             ? 1
                             : 0;
      current_pos.first++;
      add_direction(
          directions,
          pipe_from_char(lines[current_pos.first][current_pos.second]), S);
      break;
    case S:
      path_lengths[S] += (lines[current_pos.first][current_pos.second] == NS ||
                          lines[current_pos.first][current_pos.second] == NW ||
                          lines[current_pos.first][current_pos.second] == NE)
                             ? 1
                             : 0;
      current_pos.first--;
      add_direction(
          directions,
          pipe_from_char(lines[current_pos.first][current_pos.second]), N);
      break;
    case E:
      path_lengths[E] += (lines[current_pos.first][current_pos.second] == EW ||
                          lines[current_pos.first][current_pos.second] == SW ||
                          lines[current_pos.first][current_pos.second] == NW)
                             ? 1
                             : 0;
      current_pos.second++;
      add_direction(
          directions,
          pipe_from_char(lines[current_pos.first][current_pos.second]), W);
      break;
    case W:
      path_lengths[W] += (lines[current_pos.first][current_pos.second] == EW ||
                          lines[current_pos.first][current_pos.second] == SE ||
                          lines[current_pos.first][current_pos.second] == NE)
                             ? 1
                             : 0;
      current_pos.second--;
      add_direction(
          directions,
          pipe_from_char(lines[current_pos.first][current_pos.second]), E);
      break;
    }

    if (lines[current_pos.first][current_pos.second] == Pipe::START) {
      break;
    }
  }

  return std::max_element(
             path_lengths.begin(), path_lengths.end(),
             [](const auto &a, const auto &b) { return a.second < b.second; })
      ->second;
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
