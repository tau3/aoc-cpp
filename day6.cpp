#include "day6.hpp"
#include "util.hpp"
#include <cstddef>
#include <vector>

namespace Day6 {

void toggle(const pair<size_t, size_t> &left_top,
            const pair<size_t, size_t> &right_bottom,
            vector<vector<bool>> &grid) {
  for (size_t row = left_top.second; row <= right_bottom.second; row++) {
    for (size_t col = left_top.first; col <= right_bottom.first; col++) {
      grid[col][row] = !grid[col][row];
    }
  }
}

void turn(const pair<size_t, size_t> &left_top,
          const pair<size_t, size_t> &right_bottom, vector<vector<bool>> &grid,
          const bool val) {
  for (size_t row = left_top.second; row <= right_bottom.second; row++) {
    for (size_t col = left_top.first; col <= right_bottom.first; col++) {
      grid[col][row] = val;
    }
  }
}

void apply(const string &line, vector<vector<bool>> &grid) {
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
    const bool val = tokens[1] == "on";

    const string left_top = tokens[2];
    const string right_bottom = tokens[4];

    const auto left_top_tokens = util::split(left_top, ",");
    const auto right_bottom_tokens = util::split(right_bottom, ",");

    turn({stol(left_top_tokens[0]), stol(left_top_tokens[1])},
         {stol(right_bottom_tokens[0]), stol(right_bottom_tokens[1])}, grid,
         val);
  }
}

int solve_day6_pt1(const vector<string> &input) {
  vector<vector<bool>> grid(1000, vector<bool>(1000, false));
  for (const string &line : input) {
    apply(line, grid);
  }

  int result = 0;
  for (const vector<bool> &row : grid) {
    for (const bool val : row) {
      if (val) {
        result++;
      }
    }
  }
  return result;
}

} // namespace Day6
