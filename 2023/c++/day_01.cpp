// https://adventofcode.com/2023/day/1

#include "common.hpp"

#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using std::accumulate;
using std::cout;
using std::endl;
using std::ifstream;
using std::map;
using std::string;
using std::vector;

static const string DIGITS = "123456789";

void replace_words(string *line) {
  static const map<string, string> WORDS_TO_NUMS = {
      {"one", "o1e"},   {"two", "t2o"},   {"three", "t3e"},
      {"four", "f4r"},  {"five", "f5e"},  {"six", "s6x"},
      {"seven", "s7n"}, {"eight", "e8t"}, {"nine", "n9e"}};

  size_t match_start = 0;
  for (auto &pair : WORDS_TO_NUMS) {
    while ((match_start = line->find(pair.first)) != string::npos) {
      line->replace(match_start, pair.second.length(), pair.second);
      match_start += pair.second.length();
    }
  }
}

int part_1(ifstream &input) {
  vector<string> lines = get_lines(input);
  return accumulate(lines.begin(), lines.end(), 0, [](int acc, string s) {
    return acc + ((s[s.find_first_of(DIGITS)] - 0x30) * 10 +
                  (s[s.find_last_of(DIGITS)] - 0x30));
  });
}

int part_2(ifstream &input) {
  vector<string> lines = get_lines(input);
  return accumulate(lines.begin(), lines.end(), 0, [](int acc, string s) {
    replace_words(&s);
    return acc + ((s[s.find_first_of(DIGITS)] - 0x30) * 10 +
                  (s[s.find_last_of(DIGITS)] - 0x30));
  });
}

int main() {
  ifstream input("in.txt");

  cout << part_1(input) << endl;
  input.clear();
  input.seekg(ifstream::beg);
  cout << part_2(input) << endl;

  return 0;
}