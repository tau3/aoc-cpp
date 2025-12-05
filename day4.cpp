#include "day4.hpp"

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

} // namespace Day4
