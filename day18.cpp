#include "day18.hpp"

namespace Day18 {

vector<string> step(const vector<string> &grid);

int solve(vector<string> grid, const int steps) {
  for (int i = 0; i < steps; i++) {
    grid = step(grid);
  }

  int result = 0;
  for (const auto &row : grid) {
    for (const auto &column : row) {
      if (column == '#') {
        result++;
      }
    }
  }
  return result;
}

int count_on(const vector<string> &grid, const int row, const int column) {
  // clang-format off
  const vector<pair<int, int>> adjacent = {
    {column - 1, row - 1},
    {column, row - 1},
    {column + 1, row - 1},
    {column - 1, row},
    {column + 1, row},
    {column - 1, row + 1},
    {column, row + 1},
    {column + 1, row + 1}
  };
  // clang-format on

  int result = 0;
  const int height = grid.size();
  const int width = grid[0].size();
  for (const auto &cell : adjacent) {
    const int column = cell.first;
    const int row = cell.second;
    if (column < 0 || column >= width || row < 0 || row >= height) {
      continue;
    }

    if (grid[row][column] == '#') {
      result++;
    }
  }
  return result;
}

vector<string> step(const vector<string> &grid) {
  vector<string> result;
  for (int row = 0; row < grid.size(); row++) {
    string line = "";
    for (int column = 0; column < grid[0].size(); column++) {
      const int neighbors_on = count_on(grid, row, column);
      if (grid[row][column] == '#') {
        if (neighbors_on == 2 || neighbors_on == 3) {
          line += '#';
        } else {
          line += '.';
        }
      } else {
        if (neighbors_on == 3) {
          line += '#';
        } else {
          line += '.';
        }
      }
    }
    result.push_back(line);
  }
  return result;
}

} // namespace Day18
