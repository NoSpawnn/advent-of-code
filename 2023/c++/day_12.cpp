// https://adventofcode.com/2023/day/12


#include "common.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const char SPRING = '#', UNK = '?';

int part_1(ifstream &input) {
  int total = 0;
  string springs, counts;

  while (input >> springs >> counts) {
    istringstream iss(counts);
    vector<int> counts(iss);
    cout << springs << " " << counts << endl;
  }

  return total;
}

int main() {
  ifstream input("../input/day_12.txt");

  if (!input.is_open()) {
    perror(NULL);
    return -1;
  }

  cout << part_1(input) << endl;
  input.clear();
  input.seekg(ifstream::beg);
  //   cout << part_2(input) << endl;

  return 0;
}