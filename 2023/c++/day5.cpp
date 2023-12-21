
// https://adventofcode.com/2023/day/5

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int p1_total = 0, p2_total = 0;

static const regex map_line_rgx(R"(([a-z]+)-to-([a-z]+) map:)");
static const regex number_rgx(R"(\d+)");

typedef struct {
  long long dest;
  long long source;
  long long len;
} Range;

typedef struct {
  string from;
  string to;
  vector<Range> ranges;
} Map;

long long part1(vector<long long> seeds, vector<Map> maps) {
  long long lowest;
  for (auto seed : seeds) {
    long long cur_num = seed;

    for (Map &map : maps) {
      for (Range &range : map.ranges) {
        if (cur_num >= range.source && cur_num <= range.source + range.len) {
          cur_num = range.dest + (cur_num - range.source);

          break;
        }
      }
    }

    lowest = cur_num < lowest ? cur_num : lowest;
  }

  return lowest;
}

// holy fuck this is slow
long long part2(vector<long long> seeds, vector<Map> maps) {

  long long lowest;
  for (auto it = seeds.begin(); it != seeds.end(); ++it) {
    long long from = *it;
    ++it;
    long long to = *it;

    for (auto seed = from; seed < from + to; ++seed) {
      long long cur_num = seed;
      for (Map &map : maps) {
        for (Range &range : map.ranges) {
          if (cur_num >= range.source && cur_num <= range.source + range.len) {
            cur_num = range.dest + (cur_num - range.source);

            break;
          }
        }
      }

      lowest = cur_num < lowest ? cur_num : lowest;
    }
  }

  return lowest;
}

int main() {
  ifstream input("in.txt");
  string line;

  getline(input, line);
  std::istringstream iss(line);
  iss.ignore(6, ':');
  vector<long long> seeds((std::istream_iterator<long long>(iss)),
                          std::istream_iterator<long long>());

  vector<Map> maps;
  Map this_map;
  getline(input, line);
  while (getline(input, line)) {
    smatch match;

    if (line.empty()) {
      maps.push_back(this_map);

      this_map = {};

      continue;
    }

    if (regex_search(line, match, map_line_rgx)) {
      this_map.from = match[1].str();
      this_map.to = match[2].str();

      continue;
    } else {
      sregex_iterator it(line.begin(), line.end(), number_rgx), end;

      Range this_range;
      this_range.dest = strtol(it->str().c_str(), NULL, 10);
      ++it;
      this_range.source = strtol(it->str().c_str(), NULL, 10);
      ++it;
      this_range.len = strtol(it->str().c_str(), NULL, 10);

      this_map.ranges.push_back(this_range);
    }
  }

  if (!this_map.from.empty()) {
    maps.push_back(this_map);
  }

  cout << part1(seeds, maps) << endl;
  cout << part2(seeds, maps) << endl;

  return 0;
}