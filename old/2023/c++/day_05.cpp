// https://adventofcode.com/2023/day/5

#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

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

vector<long long> get_seeds(ifstream &input) {
  string line;
  getline(input, line);
  std::istringstream iss(line);
  iss.ignore(6, ':');
  return vector<long long>{(std::istream_iterator<long long>(iss)),
                           std::istream_iterator<long long>()};
}

vector<Map> get_maps(ifstream &input) {
  static const regex map_line_rgx(R"(([a-z]+)-to-([a-z]+) map:)");
  static const regex number_rgx(R"(\d+)");

  string line;
  vector<Map> maps;
  Map this_map;

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
      this_range.dest = std::stol(it->str(), NULL, 10);
      ++it;
      this_range.source = std::stol(it->str(), NULL, 10);
      ++it;
      this_range.len = std::stol(it->str(), NULL, 10);

      this_map.ranges.push_back(this_range);
    }
  }
  maps.push_back(this_map);

  return maps;
}

static long long traverse(long long current, vector<Map> maps) {
  for (Map &map : maps) {
    for (Range &range : map.ranges) {
      if (current >= range.source && current <= range.source + range.len) {
        current = range.dest + (current - range.source);
        break;
      }
    }
  }

  return current;
}

long long part_1(ifstream &input) {
  long long lowest = numeric_limits<long>::max();
  vector<long long> seeds = get_seeds(input);
  vector<Map> maps = get_maps(input);

  for (auto seed : seeds) {
    long long cur_num = traverse(seed, maps);
    lowest = std::min(cur_num, lowest);
  }

  return lowest;
}

// holy fuck this is slow
long long part_2(ifstream &input) {
  long long lowest = numeric_limits<long>::max();
  vector<long long> seeds = get_seeds(input);
  vector<Map> maps = get_maps(input);

  for (auto it = seeds.begin(); it != seeds.end(); it += 2) {
    long long from = *it;
    long long to = *(it + 1);

    for (auto seed = from; seed < from + to; ++seed) {
      long long cur_num = traverse(seed, maps);
      lowest = std::min(cur_num, lowest);
    }
  }

  return lowest;
}

int main() {
  ifstream input("../input/day_05.txt");

  if (!input.is_open()) {
    perror("ERROR");
    return -1;
  }

  cout << "PART 1 TOTAL: " << part_1(input) << endl;
  input.clear();
  input.seekg(ifstream::beg);
  // cout << "PART 2 TOTAL: " << part_2(input) << endl;

  return 0;
}