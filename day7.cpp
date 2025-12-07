#include "day7.hpp"

namespace Day7 {

int solve_day7_pt1(vector<string> &input) {
  int result = 0;
  for (size_t row = 1; row < input.size(); row++) {
    for (size_t column = 1; column < input[0].size(); column++) {
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

} // namespace Day7
