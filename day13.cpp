#include "day13.hpp"
#include "util.hpp"
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct Solution {
  size_t rows;
  size_t columns;
};

bool equal_cols(const vector<string> &input, size_t left, size_t right) {
  for (const string &line : input) {
    if (line[left] != line[right]) {
      return false;
    }
  }
  return true;
}

bool is_horizontal_border(const vector<string> &input, size_t lower) {
  int down = lower + 1;
  int up = lower - 2;
  while ((up >= 0) && (down < input.size())) {
    if (input[up] != input[down]) {
      return false;
    }
    up--;
    down++;
  }
  return true;
}

bool is_vertical_border(const vector<string> &input, size_t right) {
  int east = right + 1;
  int west = right - 2;
  while ((west >= 0) && (east < input[0].size())) {
    if (!equal_cols(input, west, east)) {
      return false;
    }
    west--;
    east++;
  }
  return true;
}

Solution solve_pattern(const vector<string> &input) {
  for (size_t i = 1; i < input.size(); ++i) {
    if (input[i] == input[i - 1]) {
      if (is_horizontal_border(input, i)) {
        return Solution{i, 0};
      }
    }
  }

  for (size_t i = 0; i < input[0].size(); ++i) {
    if (equal_cols(input, i, i - 1)) {
      if (is_vertical_border(input, i)) {
        return Solution{0, i};
      }
    }
  }

  throw invalid_argument("no solution");
}

int solve_day13_pt1(const vector<string> &input) {
  size_t start = 0;
  size_t current = 0;
  size_t columns = 0;
  size_t rows = 0;
  while (current < input.size()) {
    current++;
    if (!input[current].empty()) {
      continue;
    }
    auto slice = vector<string>(input.begin() + start, input.begin() + current);
    const Solution solution = solve_pattern(slice);
    columns += solution.columns;
    rows += solution.rows;
    start = current + 1;
  }
  if (start < current) {
    auto slice = vector<string>(input.begin() + start, input.begin() + current);
    const Solution solution = solve_pattern(slice);
    columns += solution.columns;
    rows += solution.rows;
  }
  return columns + 100 * rows;
}
