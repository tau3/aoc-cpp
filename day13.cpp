#include "day13.hpp"
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include "util.hpp"

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
      cout << "input: " << endl;
      print(input);
      cout << "rows above: " << i << endl;
      
      return Solution{i, 0};
    }
  }

  for (size_t i = 0; i < input[0].size(); ++i) {
    if (equal_cols(input, i, i - 1)) {
      cout << "input: " << endl;
      print(input);
      cout << "cols left: " << i << endl;
      
      return Solution{0, i};
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
    start = current+1;
  }
  auto slice = vector<string>(input.begin() + start, input.begin() + current);
  const Solution solution = solve_pattern(slice);
  columns += solution.columns;
  rows += solution.rows;
  start = current;
  return columns + 100 * rows;
}
