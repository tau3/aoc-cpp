#include "day5.hpp"
#include <vector>

namespace Day5 {

vector<int> to_ints(const vector<string> &input) {
  vector<int> result;
  for (const string &line : input) {
    const int val = stoi(line);
    result.push_back(val);
  }
  return result;
}

int solve_pt1(const vector<string> &input) {
  vector<int> offsets = to_ints(input);

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
  vector<int> offsets = to_ints(input);

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
