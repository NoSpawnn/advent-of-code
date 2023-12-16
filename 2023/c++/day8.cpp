// https://adventofcode.com/2023/day/8

#include <algorithm>
#include <array>
#include <atomic>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <mutex>
#include <queue>
#include <regex>
#include <string>
#include <thread>
#include <vector>

using namespace std;

#define END_NODE "ZZZ"

typedef struct Node {
  string id;
  string left;
  string right;
} Node;

static const regex rgx(R"([A-Z]{3})");
static map<string, Node> nodes;
static map<string, int> distances_traveled;
string directions;
vector<Node> p2_nodes;
int total1 = 0;
long long total2 = 1;

long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }
long long lcm(long long a, long long b) { return a * b / gcd(a, b); }

int main() {
  ifstream input("../input/day8.txt");
  input >> directions;
  string line;
  while (getline(input, line)) {
    sregex_iterator it(line.begin(), line.end(), rgx), end;
    for (; it != end; ++it) {
      string id = it->str();
      ++it;
      string left = it->str();
      ++it;
      string right = it->str();
      Node new_node = Node{id, left, right};
      nodes[id] = new_node;

      if (id[2] == 'A') {
        distances_traveled[new_node.id] = 0;
        p2_nodes.push_back(new_node);
      }
    }
  }

  Node current_node = nodes.begin()->second;
  while (current_node.id != END_NODE) {
    for (size_t i = 0; i < directions.length(); ++i) {
      if (directions[i] == 'L') {
        current_node = nodes[current_node.left];
      } else if (directions[i] == 'R') {
        current_node = nodes[current_node.right];
      }

      total1++;
    }
  }

  for (auto &start_node : p2_nodes) {
    int dir_idx = 0;
    string curr_node = start_node.id;
    while (curr_node[2] != END_NODE[2]) {
      distances_traveled[start_node.id]++;
      dir_idx = dir_idx % directions.length();

      if (directions[dir_idx] == 'L') {
        curr_node = nodes[curr_node].left;
      } else if (directions[dir_idx] == 'R') {
        curr_node = nodes[curr_node].right;
      }

      dir_idx++;
    }
  }

  for (auto [n, distance] : distances_traveled) {
    total2 = lcm(total2, distance);
  }

  cout << "PART 1 TOTAL: " << total1 << endl;
  cout << "PART 2 TOTAL: " << total2 << endl;

  return 0;
}
