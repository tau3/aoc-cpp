#include "day8.hpp"
#include <algorithm>
#include <array>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Day8 {

struct Point {
  int r;
  int c;

  explicit Point(const int r, const int c) : r(r), c(c) {}

  bool is_on_grid(const vector<string> &grid) const {
    return (r >= 0) && (c >= 0) && (r < grid.size()) && (c < grid[0].size());
  }
};

struct PointHash {
  size_t operator()(const Point &point) const {
    const auto [r, c] = point;
    return 31 * r + 17 * c;
  }
};

Point operator+(const Point &lhs, const Point &rhs) {
  return Point(lhs.r + rhs.r, lhs.c + rhs.c);
}

Point operator-(const Point &lhs, const Point &rhs) {
  return Point(lhs.r - rhs.r, lhs.c - rhs.c);
}

bool operator==(const Point &lhs, const Point &rhs) {
  return (lhs.r == rhs.r) && (lhs.c == rhs.c);
}

array<Point, 2> find_antinodes(const Point &lhs, const Point &rhs) {
  const Point d = lhs - rhs;
  return {lhs + d, rhs - d};
}

unordered_map<char, vector<Point>> group_antennas(const vector<string> &grid) {
  const size_t w = grid[0].size();
  const size_t h = grid.size();

  unordered_map<char, vector<Point>> result;
  for (size_t r = 0; r < h; ++r) {
    for (size_t c = 0; c < w; ++c) {
      const char frequency = grid[r][c];
      if (frequency == '.') {
        continue;
      }

      if (auto entry = result.find(frequency); entry != result.end()) {
        vector<Point> &points = entry->second;
        points.push_back(Point(r, c));
      } else {
        const vector<Point> points = {Point(r, c)};
        result[frequency] = points;
      }
    }
  }

  return result;
}

int solve_pt1(const vector<string> &grid) {
  unordered_map<char, vector<Point>> antennas = group_antennas(grid);
  unordered_set<Point, PointHash> result;
  for (const auto &entry : group_antennas(grid)) {
    const vector<Point> points = entry.second;
    for (size_t i = 0; i < points.size(); ++i) {
      for (size_t j = i + 1; j < points.size(); ++j) {
        const Point &lhs = points[i];
        const Point &rhs = points[j];
        const array<Point, 2> antinodes = find_antinodes(lhs, rhs);
        if (antinodes[0].is_on_grid(grid)) {
          result.insert(antinodes[0]);
        }
        if (antinodes[1].is_on_grid(grid)) {
          result.insert(antinodes[2]);
        }
      }
    }
  }
  return result.size();
}
} // namespace Day8
