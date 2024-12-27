#include "day16.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <limits>
#include <vector>

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
  cout << "at (" << start.r << "," << start.c << ")" << endl;

  if (start == end) {
    solutions.push_back(current_path);
    return;
  }

  const auto last = current_path[current_path.size() - 1];

  for (const Point &p : last.adj()) {
    if (grid[p.r][p.c] == '#') {
      continue;
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

int count_turns(const vector<Point> &path) {
  int result = 0;
  for (size_t i = 1; i < path.size() - 1; ++i) {
    const Point &prev = path[i - 1];
    const Point &current = path[i];
    const Point &next = path[i + 1];

    const bool one_row = (prev.r == current.r) && (current.r == next.r);
    const bool one_col = (prev.c == current.c) && (current.c == next.c);
    if (!(one_col || one_row)) {
      ++result;
    }
  }

  if (path[0].c == path[1].c) {
    ++result;
  }

  return result;
}

int score(const vector<Point> &path) {
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
    const int s = score(path);
    result = min(result, s);
  //   for (const Point &p : path) {
  //     cout << "(" << p.r << "," << p.c << ")-->";
  //   }
  //   cout << endl;
  }
  return result;
}

} // namespace Day16
