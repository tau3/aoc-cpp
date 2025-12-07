#include "day7.hpp"
#include "util.hpp"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace Day7 {

int solve_day7_pt1(vector<string> &input) {
  int result = 0;
  for (size_t row = 1; row < input.size(); row++) {
    for (size_t column = 0; column < input[0].size(); column++) {
      if ((row == 1) && (input[0][column] == 'S')) {
        input[row][column] = '|';
        continue;
      }

      if (input[row][column] == '^') {
        if (input[row - 1][column] == '|') {
          input[row][column - 1] = '|';
          input[row][column + 1] = '|';
          column++;
          result++;
        }
      } else if ((input[row][column] == '.') &&
                 (input[row - 1][column] == '|')) {
        input[row][column] = '|';
      }
    }
  }
  return result;
}

using Memo = unordered_map<util::Point, uint64_t, util::PointHash>;

uint64_t count_ways_to(const vector<string> &input, const size_t row,
                       const size_t column, Memo &memo) {
  if (memo.find({row, column}) != memo.end()) {
    return memo[{row, column}];
  }

  const char upper = input[row - 1][column];
  if (upper == 'S') {
    return 1;
  }

  uint64_t result = 0;
  if ((column < (input[0].size() - 1)) && (input[row][column + 1] == '^')) {
    result += count_ways_to(input, row, column + 1, memo);
  }
  if ((column > 0) && (input[row][column - 1] == '^')) {
    result += count_ways_to(input, row, column - 1, memo);
  }
  if (upper == '|') {
    result += count_ways_to(input, row - 1, column, memo);
  }
  memo[{row, column}] = result;
  return result;
}

uint64_t solve_day7_pt2(vector<string> &input) {
  solve_day7_pt1(input);

  for (const auto &line : input) {
    cout << line << endl;
  }

  const size_t last_row = input.size() - 1;
  uint64_t result = 0;
  Memo memo;
  for (size_t column = 0; column < input[0].size(); column++) {
    if (input[last_row][column] == '|') {
      result += count_ways_to(input, last_row, column, memo);
    }
  }
  return result;
}

} // namespace Day7
