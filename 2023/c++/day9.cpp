// https://adventofcode.com/2023/day/9

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

static vector<int> find_diffs(vector<int> nums) {
  vector<int> diffs;

  for (auto it = next(nums.begin()); it != nums.end(); ++it) {
    diffs.push_back(*it - *(prev(it)));
  }

  return diffs;
}

static int find_next(vector<int> nums) {
  vector<int> diffs = find_diffs(nums);

  if (all_of(diffs.begin(), diffs.end(), [](int x) { return x == 0; })) {
    return nums.back() + diffs.back();
  }

  return nums.back() + find_next(diffs);
}

static int find_prev(vector<int> nums) {
  vector<int> diffs = find_diffs(nums);

  if (all_of(diffs.begin(), diffs.end(), [](int x) { return x == 0; })) {
    return nums.front() - diffs.front();
  }

  return nums.front() - find_prev(diffs);
}

int main() {
  ifstream input("in.txt");

  int total1 = 0;
  int total2 = 0;
  string line;
  while (getline(input, line)) {
    istringstream iss(line);
    vector<int> nums(istream_iterator<int>(iss), {});

    total1 += find_next(nums);
    total2 += find_prev(nums);

    nums.clear();
  }

  cout << total1 << endl;
  cout << total2 << endl;

  return 0;
}