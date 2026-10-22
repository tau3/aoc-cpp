#include "day5.hpp"
#include <fstream>

namespace Day5 {

int solve_pt1(const vector<string> &input) {
  vector<int> offsets;
  for (const string &line : input) {
    const int val = stoi(line);
    offsets.push_back(val);
  }

  int pos = 0;
  int count = 0;
  while ((pos >= 0) && (pos < offsets.size())) {
    int &offset = offsets[pos];
    pos += offset;
    offset++;
    count++;
  }

  return count;
}

int solve_pt2(const vector<string> &input) {
  vector<int> offsets;
  for (const string &line : input) {
    const int val = stoi(line);
    offsets.push_back(val);
  }

  int pos = 0;
  int count = 0;
  while ((pos >= 0) && (pos < offsets.size())) {
    int &offset = offsets[pos];
    pos += offset;
    if (offset >= 3) {
      --offset;
    } else {
      offset++;
    }
    count++;
  }

  return count;
}

} // namespace Day5
