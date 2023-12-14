#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#define RED "red"
#define BLUE "blue"
#define GREEN "green"

int get_game_id_and_cut_str(std::string *s);
std::vector<std::string> split_into_sets(std::string line);

const std::map<std::string, int> MAX_COUNTS = {
    {RED, 12}, {BLUE, 14}, {GREEN, 13}};

int main() {
  std::ifstream input("../input/day2.txt");

  if (!input.is_open()) {
    perror("ERROR - failed to open file:");

    return -1;
  }

  int total1 = 0;
  int total2 = 0;
  std::string line;
  while (std::getline(input, line)) {
    int game_id = get_game_id_and_cut_str(&line);

    bool valid = true;
    std::string color;
    int count;
    std::vector<std::string> sets = split_into_sets(line);
    std::map<std::string, int> minimum_a = {{RED, 0}, {BLUE, 0}, {GREEN, 0}};

    for (auto set : sets) {
      std::istringstream iss(set);
      std::map<std::string, int> counts = {{RED, 0}, {BLUE, 0}, {GREEN, 0}};

      while (iss >> count) {
        iss >> color;

        color.erase(std::remove(color.begin(), color.end(), ','), color.end());

        counts[color] += count;

        if (count > minimum_a[color]) {
          minimum_a[color] = count;
        }
      }

      for (auto [color, count] : counts) {
        if (count > MAX_COUNTS.at(color)) {
          valid = false;
          break;
        }
      }
    }

    total2 += minimum_a[RED] * minimum_a[BLUE] * minimum_a[GREEN];

    if (valid) {
      total1 += game_id;
    }
  }

  std::cout << "P1 TOTAL: " << total1 << std::endl;
  std::cout << "P2 TOTAL: " << total2 << std::endl;

  return 0;
}

int get_game_id_and_cut_str(std::string *s) {
  size_t colon_pos = s->find(":");

  int id = strtol(s->substr(4, colon_pos).c_str(), NULL, 10);

  *s = s->substr(colon_pos + 2, s->length() - colon_pos - 1);

  return id;
}

std::vector<std::string> split_into_sets(std::string line) {
  std::vector<std::string> draws;

  size_t pos = 0;
  while (pos != std::string::npos) {
    pos = line.find(";");
    draws.push_back(line.substr(0, pos));
    line = line.substr(pos + 2, line.length() - pos - 1);
  }

  return draws;
}