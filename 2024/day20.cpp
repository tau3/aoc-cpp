#include "day20.hpp"
#include <cassert>
#include <cstddef>
#include <stack>
#include <unordered_map>

namespace Day20 {

struct Point {
  int r;
  int c;
};

bool operator==(const Point &lhs, const Point &rhs) {
  return (lhs.r == rhs.r) && (lhs.c == rhs.c);
}

struct PointHash {
  size_t operator()(const Point &point) const {
    const auto [r, c] = point;
    return 31 * r + 17 * c;
  }
};

Point extract_min(vector<Point> &queue,
                  const unordered_map<Point, int, PointHash> distances) {
  assert(!queue.empty());

  Point result = queue[0];
  int min_distance = distances.at(result);
  size_t index = 0;
  for (size_t i = 1; i < queue.size(); ++i) {
    const Point current = queue[i];
    const int distance = distances.at(current);
    if (distance < min_distance) {
      result = current;
      min_distance = distance;
      index = i;
    }
  }
  queue.erase(queue.begin() + index);
  return result;
}

vector<Point> adjacent(const Point &point, const vector<string> &grid) {
  const auto [x, y] = point;
  vector<Point> all = {{x - 1, y}, {x + 1, y}, {x, y + 1}, {x, y - 1}};

  vector<Point> result;
  for (const Point &point : all) {
    if (grid[point.r][point.c] == '#') {
      continue;
    }

    if ((point.r >= 0) && (point.c >= 0) && (point.r < (int)grid.size()) &&
        (point.c < (int)grid[0].size())) {
      result.push_back(point);
    }
  }

  return result;
}

int run(const Point &start, const vector<string> &grid, const bool is_pt_2) {
  stack<pair<Point, int>> s;
  s.push({start, 0});
  unordered_map<Point, int, PointHash> distances;
  while (!s.empty()) {
    const auto [v, distance] = s.top();
    s.pop();
    if (distances.find(v) == distances.end()) {
      distances[v] = distance;
      for (const Point w : adjacent(v, grid)) {
        s.push({w, distance + 1});
      }
    }
  }

  vector<Point> path;
  for (const auto &[k, _] : distances) {
    path.push_back(k);
  }

  int result = 0;
  for (size_t i = 0; i < path.size(); ++i) {
    for (size_t j = i + 1; j < path.size(); ++j) {
      const Point &lhs = path[i];
      const Point &rhs = path[j];
      const int dist = abs(lhs.r - rhs.r) + abs(lhs.c - rhs.c);
      const int saved = abs(distances[lhs] - distances[rhs]);
      if (saved >= 100 + dist) {
        if (!is_pt_2 && (dist == 2)) {
          ++result;
        } else if (is_pt_2 && (dist <= 20)) {
          ++result;
        }
      }
    }
  }

  return result;
}

int solve(const vector<string> &input, const bool is_pt_2) {
  Point start;
  for (size_t r = 0; r < input.size(); ++r) {
    for (size_t c = 0; c < input[0].size(); ++c) {
      if (input[r][c] == 'S') {
        start = {int(r), int(c)};
        break;
      }
    }
  }
  return run(start, input, is_pt_2);
};

int solve_day20_pt1(const vector<string> &input) { return solve(input, false); }

int solve_day20_pt2(const vector<string> &input) { return solve(input, true); }
} // namespace Day20
