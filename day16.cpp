#include "day16.hpp"
#include <algorithm>
#include <limits>
#include <vector>

namespace Day16 {

struct Point {
  size_t row;
  size_t col;

  vector<Point> adjacent() const {
    return {{row - 1, col}, {row, col + 1}, {row + 1, col}, {row, col - 1}};
  }
};

bool operator==(const Point &lhs, const Point &rhs) {
  return lhs.col == rhs.col && lhs.row == rhs.row;
}

void dfs(const Point &start, const Point &end, vector<vector<Point>> &solutions,
         vector<Point> &current_path, const vector<string> &grid) {
  if (start == end) {
    solutions.push_back(current_path);
    return;
  }

  const auto last = current_path[current_path.size() - 1];

  for (const Point &point : last.adjacent()) {
    if (grid[point.row][point.col] == '#') {
      continue;
    }

    if (find(current_path.begin(), current_path.end(), point) !=
        current_path.end()) {
      continue;
    }

    vector<Point> new_path = current_path;
    new_path.push_back(point);
    dfs(point, end, solutions, new_path, grid);
  }
}

int count_turns(const vector<Point> &path) {
  int result = 0;
  for (size_t i = 1; i < path.size() - 1; ++i) {
    const Point &prev = path[i - 1];
    const Point &current = path[i];
    const Point &next = path[i + 1];

    const bool one_row = (prev.row == current.row) && (current.row == next.row);
    const bool one_col = (prev.col == current.col) && (current.col == next.col);
    if (!(one_col || one_row)) {
      ++result;
    }
  }

  if (path[0].col == path[1].col) {
    ++result;
  }

  return result;
}

int calc_score(const vector<Point> &path) {
  const size_t steps = path.size() - 1;
  const int turns = count_turns(path);
  return steps + turns * 1000;
}

int solve_day16_pt1(const vector<string> &grid) {
  const Point current{grid.size() - 2, 1};
  const Point target = {1, grid[0].size() - 2};

  vector<vector<Point>> paths;
  vector<Point> path = {current};
  dfs(current, target, paths, path, grid);

  int result = numeric_limits<int>::max();
  for (const auto &path : paths) {
    const int score = calc_score(path);
    result = min(result, score);
  }
  return result;
}

} // namespace Day16
