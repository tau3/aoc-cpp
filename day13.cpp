#include "day13.hpp"
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

Solution solve_pattern(const vector<string> &input) {
  for (size_t i = 1; i < input.size(); ++i) {
    if (input[i] == input[i - 1]) {
      return Solution{i, 0};
    }
  }

  for (size_t i = 0; i < input[0].size(); ++i) {
    if (equal_cols(input, i, i - 1)) {
      return Solution{0, i};
    }
  }

  throw invalid_argument("no solution");
}

int solve(const vector<string> &input) {
  size_t start = 0;
  size_t current = 0;
  size_t columns = 0;
  size_t rows = 0;
  while (current < input.size()) {
    if (!input[current].empty()) {
      current++;
      continue;
    }
    const Solution solution = solve_pattern(
        vector<string>(input.begin() + start, input.begin() + current));
    columns += solution.columns;
    rows += solution.rows;
    start = current;
  }
  const Solution solution = solve_pattern(
      vector<string>(input.begin() + start, input.begin() + current));
  columns += solution.columns;
  rows += solution.rows;
  start = current;
  return columns + 100 * rows;
}
