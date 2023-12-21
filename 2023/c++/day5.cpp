
// https://adventofcode.com/2023/day/5

#include <algorithm>
#include <array>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int p1_total = 0, p2_total = 0;

static const regex map_line_rgx(R"(([a-z]+)-to-([a-z]+) map:)");
static const regex number_rgx(R"(\d+)");

typedef struct {
  long dest;
  long source;
  long len;
} Range;

typedef struct {
  string from;
  string to;
  vector<Range> ranges;
} Map;

int main() {
  ifstream input("in.txt");
  string line;

  getline(input, line);
  std::istringstream iss(line);
  iss.ignore(6, ':');
  vector<long> seeds((std::istream_iterator<long>(iss)),
                     std::istream_iterator<long>());

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
      sregex_iterator iter(line.begin(), line.end(), number_rgx), end;

      Range this_range;
      this_range.dest = strtol(iter->str().c_str(), NULL, 10);
      ++iter;
      this_range.source = strtol(iter->str().c_str(), NULL, 10);
      ++iter;
      this_range.len = strtol(iter->str().c_str(), NULL, 10);

      this_map.ranges.push_back(this_range);
    }
  }

  if (!this_map.from.empty()) {
    maps.push_back(this_map);
  }

  vector<long> locations;
  for (auto seed : seeds) {
    long cur_num = seed;

    for (auto &map : maps) {
      for (auto &range : map.ranges) {
        if (cur_num >= range.source && cur_num <= range.source + range.len) {
          cur_num = range.dest + (cur_num - range.source);

          break;
        }
      }
    }

    locations.push_back(cur_num);
  }

  cout << *min_element(locations.begin(), locations.end()) << endl;

  return 0;
}