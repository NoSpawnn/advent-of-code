// https://adventofcode.com/2023/day/6

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

static const regex number_regex(R"([0-9]+)");
vector<int> times, distances;
int total1 = 1, total2 = 0;

int main() {
  ifstream input("../input/day6.txt");

  string line;
  int line_no = 0;
  while (getline(input, line)) {
    sregex_iterator iter(line.begin(), line.end(), number_regex), end;

    for (; iter != end; ++iter) {
      if (line_no == 0) {
        times.push_back(strtol(iter->str().c_str(), NULL, 10));
      } else {
        distances.push_back(strtol(iter->str().c_str(), NULL, 10));
      }
    }

    line_no++;
  }

  assert(times.size() == distances.size());

  for (size_t race_no = 0; race_no < times.size(); ++race_no) {
    int time_limit = times[race_no];
    int distance_to_beat = distances[race_no];

    int wins = 0;
    bool has_won = false;
    for (size_t held = 0; held < time_limit; ++held) {
      int distance = held * (time_limit - held);

      if (has_won && distance < distance_to_beat) {
        break;
      }

      if (distance > distance_to_beat) {
        wins++;
        has_won = true;
      }
    }

    total1 *= wins;
  }

  stringstream p2_time, p2_distance;
  for (size_t i = 0; i < times.size(); ++i) {
    p2_time << times[i];
    p2_distance << distances[i];
  }
  long time_limit = strtol(p2_time.str().c_str(), NULL, 10);
  long distance_to_beat = strtol(p2_distance.str().c_str(), NULL, 10);

  bool has_won = false;
  for (size_t held = 0; held < time_limit; ++held) {
    long distance = held * (time_limit - held);

    if (has_won && distance < distance_to_beat) {
      break;
    }

    if (distance > distance_to_beat) {
      total2++;
      has_won = true;
    }
  }

  cout << "PART 1 TOTAL: " << total1 << '\n';
  cout << "PART 2 TOTAL: " << total2 << endl;

  return 0;
}