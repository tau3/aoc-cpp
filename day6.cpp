#include "day6.hpp"
#include "util.hpp"
#include <cstddef>
#include <vector>

#define PT2

namespace Day6 {

using Grid = vector<vector<int>>;

void toggle(const pair<size_t, size_t> &left_top,
            const pair<size_t, size_t> &right_bottom, Grid &grid) {
  for (size_t row = left_top.second; row <= right_bottom.second; row++) {
    for (size_t col = left_top.first; col <= right_bottom.first; col++) {
#ifdef PT2
      grid[col][row] += 2;
#else
      grid[col][row] = 1 - grid[col][row];
#endif
    }
  }
}

void turn(const pair<size_t, size_t> &left_top,
          const pair<size_t, size_t> &right_bottom, Grid &grid, const int val) {
  for (size_t row = left_top.second; row <= right_bottom.second; row++) {
    for (size_t col = left_top.first; col <= right_bottom.first; col++) {
#ifdef PT2
      int &num = grid[col][row];
      num += val;
      if (num < 0) {
        num = 0;
      }
#else
      grid[col][row] = val;
#endif
    }
  }
}

void apply(const string &line, Grid &grid) {
  const vector<string> tokens = util::split(line, " ");
  const string command = tokens[0];
  if (command == "toggle") {
    const string left_top = tokens[1];
    const string right_bottom = tokens[3];

    const auto left_top_tokens = util::split(left_top, ",");
    const auto right_bottom_tokens = util::split(right_bottom, ",");

    toggle({stol(left_top_tokens[0]), stol(left_top_tokens[1])},
           {stol(right_bottom_tokens[0]), stol(right_bottom_tokens[1])}, grid);
  } else {
    const int val = tokens[1] == "on" ? 1 : 0;

    const string left_top = tokens[2];
    const string right_bottom = tokens[4];

    const auto left_top_tokens = util::split(left_top, ",");
    const auto right_bottom_tokens = util::split(right_bottom, ",");

    turn({stol(left_top_tokens[0]), stol(left_top_tokens[1])},
         {stol(right_bottom_tokens[0]), stol(right_bottom_tokens[1])}, grid,
         val);
  }
}

long solve_day6_pt1(const vector<string> &input) {
  Grid grid(1000, vector<int>(1000, 0));
  for (const string &line : input) {
    apply(line, grid);
  }

  long result = 0;
  for (const vector<int> &row : grid) {
    for (const int val : row) {
#ifdef PT2
      result += val;
#else
      if (val == 1) {
        result++;
      }
#endif
    }
  }
  return result;
}

} // namespace Day6
