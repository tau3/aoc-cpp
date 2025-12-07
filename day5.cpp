#include "day5.hpp"
#include "util.hpp"
#include <algorithm>
#include <deque>
#include <string>
#include <utility>
#include <vector>

namespace Day5 {

using Range = pair<long, long>;
using Ranges = vector<Range>;
using RangesQ = deque<Range>;

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
      const vector<string> tokens = util::split(line, "-");
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

bool has_overlap(const Range &left, const Range &right) {
  return (left.first <= right.second) && (right.first <= left.second);
}

void merge(Range &left, const Range &right) {
  left.first = min(left.first, right.first);
  left.second = max(left.second, right.second);
}

void merge(RangesQ &ranges) {
  size_t cycles_no_merge = 0;
  do {
    bool merges_occured = false;
    if (ranges.size() == 1) {
      break;
    }
    const Range current = ranges.front();
    ranges.pop_front();
    for (Range &range : ranges) {
      if (has_overlap(range, current)) {
        merge(range, current);
        merges_occured = true;
        cycles_no_merge = 0;
        break;
      }
    }
    if (!merges_occured) {
      ranges.push_back(current);
      cycles_no_merge++;
    }
  } while (cycles_no_merge < ranges.size());
}

long solve_day5_pt2(const vector<string> &input) {
  RangesQ ranges;
  for (const string &line : input) {
    if (line.empty()) {
      break;
    }

    const vector<string> tokens = util::split(line, "-");
    const long start = stol(tokens[0]);
    const long finish = stol(tokens[1]);
    Range current = {start, finish};
    ranges.push_back(current);
  }

  merge(ranges);

  long result = 0;
  for (const auto &[start, finish] : ranges) {
    result += (finish - start + 1);
  }
  return result;
}

} // namespace Day5
