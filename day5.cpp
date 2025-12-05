#include "day5.hpp"
#include "util.hpp"
#include <string>
#include <utility>
#include <vector>

namespace Day5 {

using Ranges = vector<pair<long, long>>;

bool containts(const Ranges &ranges, const long num) {
  for (const auto &[start, end] : ranges) {
    if ((num >= start) && (num <= end)) {
      return true;
    }
  }
  return false;
}

int solve_day5_pt1(const vector<string> &input) {
  int result = 0;
  bool parsing_ranges = true;
  Ranges ranges;
  for (const string &line : input) {
    if (line.empty()) {
      parsing_ranges = false;
      continue;
    }

    if (parsing_ranges) {
      const vector<string> tokens = split(line, "-");
      const long start = stol(tokens[0]);
      const long finish = stol(tokens[1]);
      ranges.push_back({start, finish});
    } else {
      const long num = stol(line);
      if (containts(ranges, num)) {
        result++;
      }
    }
  }
  return result;
}

} // namespace Day5
