#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

void replace_words(std::string *line);
std::array<int, 2> find_numbers(std::string s);

const std::map<std::string, std::string> WORDS_TO_NUMS = {
    {"one", "o1e"},   {"two", "t2o"},   {"three", "t3e"},
    {"four", "f4r"},  {"five", "f5e"},  {"six", "s6x"},
    {"seven", "s7n"}, {"eight", "e8t"}, {"nine", "n9e"}};

int main() {
  std::ifstream input("day1_input.txt");

  if (!input.is_open()) {
    perror("ERROR - failed to open file:");
  }

  std::string line;
  std::vector<std::array<int, 2>> numbers1;
  std::vector<std::array<int, 2>> numbers2;
  while (input >> line) {
    numbers1.push_back(find_numbers(line));

    replace_words(&line);
    numbers2.push_back(find_numbers(line));
  }

  int p1_total = 0;
  for (auto v : numbers1) {
    p1_total += v[0] * 10 + v[1];
  }

  int p2_total = 0;
  for (auto v : numbers2) {
    p2_total += v[0] * 10 + v[1];
  }

  std::cout << "P1 TOTAL: " << p1_total << std::endl;
  std::cout << "P2 TOTAL: " << p2_total << std::endl;

  return 0;
}

std::array<int, 2> find_numbers(std::string s) {
  std::array<int, 2> numbers;

  // Find first number
  for (size_t i = 0; i < s.length(); i++) {
    if (std::isdigit(s[i])) {
      numbers[0] = s[i] - '0';

      break;
    }
  }

  // Find last number
  for (size_t i = s.length() - 1; i >= 0; i--) {
    if (std::isdigit(s[i])) {
      numbers[1] = s[i] - '0';

      break;
    }
  }

  return numbers;
}

void replace_words(std::string *line) {
  size_t start = 0;

  for (auto [word, replace] : WORDS_TO_NUMS) {
    while ((start = line->find(word)) != std::string::npos) {
      line->replace(start, replace.length(), replace);
      start += replace.length();
    }
  }
}