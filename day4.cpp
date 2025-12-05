#include "day4.hpp"
#include <cstddef>
#include <utility>
#include <vector>

namespace Day4 {

int solve_day4_pt1(const vector<string> &input) {
  int result = 0;
  for (int row = 0; row < input.size(); row++) {
    for (int column = 0; column < input.size(); column++) {
      if (input[row][column] != '@') {
        continue;
      }
      int count = 0;
      for (int column_shift = -1; column_shift <= 1; column_shift++) {
        for (int row_shift = -1; row_shift <= 1; row_shift++) {
          if ((column_shift == 0) && (row_shift == 0)) {
            continue;
          }

          const int column_adj = column + column_shift;
          const int row_adj = row + row_shift;

          if ((column_adj < 0) || (row_adj < 0) ||
              (column_adj >= input[0].length()) || (row_adj >= input.size())) {
            continue;
          }

          if (input[row_adj][column_adj] == '@') {
            count++;
          }
        }
      }
      if (count < 4) {
        result++;
      }
    }
  }
  return result;
}

vector<pair<size_t, size_t>> find_removable(const vector<string> &input) {
  vector<pair<size_t, size_t>> result;
  for (int row = 0; row < input.size(); row++) {
    for (int column = 0; column < input.size(); column++) {
      if (input[row][column] != '@') {
        continue;
      }
      int count = 0;
      for (int column_shift = -1; column_shift <= 1; column_shift++) {
        for (int row_shift = -1; row_shift <= 1; row_shift++) {
          if ((column_shift == 0) && (row_shift == 0)) {
            continue;
          }

          const int column_adj = column + column_shift;
          const int row_adj = row + row_shift;

          if ((column_adj < 0) || (row_adj < 0) ||
              (column_adj >= input[0].length()) || (row_adj >= input.size())) {
            continue;
          }

          if (input[row_adj][column_adj] == '@') {
            count++;
          }
        }
      }
      if (count < 4) {
        result.push_back({row, column});
      }
    }
  }
  return result;
}

int solve_day4_pt2(vector<string> &input) {
  vector<pair<size_t, size_t>> removable;
  int result = 0;
  do {
    removable = find_removable(input);
    result += removable.size();
    for (const auto &[row, column] : removable) {
      input[row][column] = '.';
    }
  } while (!removable.empty());
  return result;
}

} // namespace Day4
