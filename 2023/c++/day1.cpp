// https://adventofcode.com/2023/day/1

#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int p1_total = 0;
int p2_total = 0;

void replace_words(string *line) {
  static const map<string, string> WORDS_TO_NUMS = {
      {"one", "o1e"},   {"two", "t2o"},   {"three", "t3e"},
      {"four", "f4r"},  {"five", "f5e"},  {"six", "s6x"},
      {"seven", "s7n"}, {"eight", "e8t"}, {"nine", "n9e"}};

  size_t match_start = 0;
  for (auto [match, replace] : WORDS_TO_NUMS) {
    while ((match_start = line->find(match)) != string::npos) {
      line->replace(match_start, replace.length(), replace);
      match_start += replace.length();
    }
  }
}

int main() {
  ifstream input("../input/day1.txt");

  if (!input.is_open()) {
    perror("ERROR - failed to open file:");
  }

  string line;
  while (input >> line) {
    p1_total += (line[line.find_first_of("123456789")] - 0x30) * 10 +
                (line[line.find_last_of("123456789")] - 0x30);

    replace_words(&line);
    p2_total += (line[line.find_first_of("123456789")] - 0x30) * 10 +
                (line[line.find_last_of("123456789")] - 0x30);
  }

  cout << "P1 TOTAL: " << p1_total << endl;
  cout << "P2 TOTAL: " << p2_total << endl;

  input.close();
  return 0;
}