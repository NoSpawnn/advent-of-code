// https://adventofcode.com/2023/day/9

#include "common.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

using std::ifstream;
using std::istream_iterator;
using std::istringstream;
using std::string;
using std::vector;

template <typename T> bool zeroed(const vector<T> &sequence) {
  return std::all_of(sequence.begin(), sequence.end(),
                     [](T x) { return x == 0; });
}

static vector<int> find_diffs(const vector<int> &nums) {
  vector<int> diffs;

  for (auto it = next(nums.begin()); it != nums.end(); ++it) {
    diffs.push_back(*it - *(prev(it)));
  }

  return diffs;
}

static int find_next(const vector<int> &nums) {
  vector<int> diffs = find_diffs(nums);

  return zeroed(diffs) ? nums.back() + diffs.back()
                       : nums.back() + find_next(diffs);
}

static int find_prev(const vector<int> &nums) {
  vector<int> diffs = find_diffs(nums);

  return zeroed(diffs) ? nums.front() - diffs.front()
                       : nums.front() - find_prev(diffs);
}

static int part_1(ifstream &input) {
  vector<string> lines = get_lines(input);

  return std::accumulate(lines.begin(), lines.end(), 0, [](int acc, string s) {
    istringstream iss(s);
    vector<int> nums(istream_iterator<int>(iss), {});
    return acc += find_next(nums);
  });
}

static int part_2(ifstream &input) {
  vector<string> lines = get_lines(input);

  return std::accumulate(lines.begin(), lines.end(), 0, [](int acc, string s) {
    istringstream iss(s);
    vector<int> nums(istream_iterator<int>(iss), {});
    return acc += find_prev(nums);
  });
}

int main() {
  ifstream input("../input/day_09.txt");

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