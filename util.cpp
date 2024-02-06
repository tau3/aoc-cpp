#include <string>
#include <vector>
#include <fstream>

#include "util.hpp"

using namespace std;

vector<string> read_file(const string &path) {
  vector<string> lines;
  ifstream input(path);
  string line;
  while (getline(input, line)) {
    lines.push_back(line);
  }
  return lines;
}
