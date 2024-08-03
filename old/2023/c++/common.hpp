#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::string;
using std::vector;

inline static vector<string> get_lines(ifstream &ifs) {
  vector<string> lines;

  string line;
  while (getline(ifs, line)) {
    lines.push_back(line);
  }

  return lines;
}