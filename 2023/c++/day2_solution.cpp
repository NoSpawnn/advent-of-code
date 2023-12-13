/*
1. Read line (1 game)
2. Get game ID
3. Split line into sets by semicolon
4. Split sets into individual draws
5. Split draw into number and color
6. Total up colors for each draw and compare to ensure valid
*/

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

const std::map<std::string, int> MAX_COUNTS = {
    {RED, 12}, {BLUE, 14}, {GREEN, 13}};

int main() {
  std::ifstream input("day2_input.txt");

  if (!input.is_open()) {
    perror("ERROR - failed to open file:");
  }

  int total = 0;
  std::string line;
  while (std::getline(input, line)) {
    int game_id = get_game_id_and_cut_str(&line);

    std::map<std::string, int> counts = {{RED, 0}, {BLUE, 0}, {GREEN, 0}};

    std::istringstream iss(line);
    std::string word;
    int count;
    while (iss >> count) {
      iss >> word;

      word.erase(std::remove(word.begin(), word.end(), ','), word.end());
      word.erase(std::remove(word.begin(), word.end(), ';'), word.end());

      counts[word] += count;
    }

    if (!(counts.at(RED) > MAX_COUNTS.at(RED) ||
          counts.at(BLUE) > MAX_COUNTS.at(BLUE) ||
          counts.at(GREEN) > MAX_COUNTS.at(GREEN))) {
      total += game_id;
    }
  }

  std::cout << "P1 TOTAL: " << total << std::endl;
  return 0;
}

int get_game_id_and_cut_str(std::string *s) {
  size_t colon_pos = s->find(":");
  int id = strtol(s->substr(4, colon_pos).c_str(), NULL, 10);

  *s = s->substr(colon_pos + 2, s->length() - 1);

  return id;
}
