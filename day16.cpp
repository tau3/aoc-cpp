#include "day16.hpp"
#include <algorithm>
#include <iostream>

namespace Day16 {

struct Point {
  size_t r;
  size_t c;

  vector<Point> adj() const {
    return {{r - 1, c}, {r, c + 1}, {r + 1, c}, {r, c - 1}};
  }
};

bool operator==(const Point &lhs, const Point &rhs) {
  return lhs.c == rhs.c && lhs.r == rhs.r;
}

void dfs(const Point &start, const Point &end, vector<vector<Point>> &solutions,
         vector<Point> &current_path, const vector<string> &grid) {
  if (start == end) {
    solutions.push_back(current_path);
    return;
  }

  const auto last = current_path[current_path.size() - 1];

  for (const Point &p : last.adj()) {
    if (grid[p.r][p.c] == '#') {
      continue;
    }

    if (current_path.size() > 1) {
      if (p == current_path[current_path.size() - 2]) {
        continue;
      }
    }

    if (find(current_path.begin(), current_path.end(), p) !=
        current_path.end()) {
      continue;
    }

    vector<Point> new_path = current_path;
    new_path.push_back(p);
    dfs(p, end, solutions, new_path, grid);
  }
}

int solve_day16_pt1(const vector<string> &grid) {
  const Point current{grid.size() - 2, 1};
  const Point target = {1, grid[0].size() - 1};

  vector<vector<Point>> result;
  vector<Point> path = {current};
  dfs(current, target, result, path, grid);

  for (const auto &path : result) {
    for (const Point &p : path) {
      cout << "(" << p.r << "," << p.c << ")-->";
    }
    cout << endl;
  }
  return 0;
}

} // namespace Day16
