// https://adventofcode.com/2023/day/6

#include <cassert>
#include <cmath>
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
  ifstream input("../input/day_06.txt");

  if (!input.is_open()) {
    perror("ERROR");
    return -1;
  }

  string line;
  int line_no = 0;
  while (getline(input, line)) {
    sregex_iterator iter(line.begin(), line.end(), number_regex), end;

    for (; iter != end; ++iter) {
      if (line_no == 0) {
        times.push_back(std::stol(iter->str(), NULL, 10));
      } else {
        distances.push_back(std::stol(iter->str(), NULL, 10));
      }
    }

    line_no++;
  }

  assert(times.size() == distances.size());

  for (size_t race_no = 0; race_no < times.size(); ++race_no) {
    float disc = pow(times[race_no], 2) - 4 * distances[race_no];

    if (disc <= 0) {
      return -1;
    }

    float sol1 = (times[race_no] + sqrt(disc)) / 2;
    float sol2 = (times[race_no] - sqrt(disc)) / 2;
    total1 *= floor(sol1) - ceil(sol2) + ((sol1 > sol2) ? 1 : -1);
  }

  stringstream p2_time, p2_distance;
  for (size_t i = 0; i < times.size(); ++i) {
    p2_time << times[i];
    p2_distance << distances[i];
  }
  long time_limit = std::stol(p2_time.str(), NULL, 10);
  long distance_to_beat = std::stol(p2_distance.str(), NULL, 10);

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