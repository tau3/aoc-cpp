#include "day12.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <type_traits>
#include <unordered_set>
#include <vector>

namespace Day12 {

struct Point {
  int r;
  int c;

  vector<Point> adjacent() const {
    return {{r - 1, c}, {r, c + 1}, {r + 1, c}, {r, c - 1}};
  }
};

bool operator==(const Point &lhs, const Point &rhs) {
  return (lhs.c == rhs.c) && (lhs.r == rhs.r);
}

struct PointHash {
  size_t operator()(const Point &point) const {
    const auto [r, c] = point;
    return 31 * r + 17 * c;
  }
};

using Region = unordered_set<Point, PointHash>;

class Grid {
  vector<string> grid;

  Grid() {};

public:
  Grid(vector<string> grid) : grid(grid) {};

  char at(const Point &point) const { return grid[point.r][point.c]; }

  size_t width() const { return grid[0].size(); }

  size_t height() const { return grid.size(); }

  void drop_oob(vector<Point> &points) const {
    points.erase(
        remove_if(points.begin(), points.end(), [this](const Point &point) {
          return (point.c < 0) || (point.r < 0) || (point.c >= width()) ||
                 (point.r >= height());
        }));
  }
};

void add_all(Region &lhs, const Region &rhs) {
  for (const Point &point : rhs) {
    lhs.insert(point);
  }
}

unordered_set<Point, PointHash> region(const Grid &grid,
                                       unordered_set<Point, PointHash> &visited,
                                       const Point &current) {
  visited.insert(current);
  cout << "visit " << grid.at(current) << " (" << current.r << "," << current.c << ")" << endl;

  unordered_set<Point, PointHash> result{current};
  auto adj = current.adjacent();
  grid.drop_oob(adj);
  for (const Point &point : adj) {
    if (visited.find(point) != visited.end()) {
      continue;
    }

    if (grid.at(current) == grid.at(point)) {
      // result.insert(point);
      add_all(result, region(grid, visited, point));
    }
  }

  // cout << "region: " << result.size();

  return result;
}

int perimeter(const unordered_set<Point, PointHash> &region, const Grid &grid) {
  int result = 0;
  for (const Point &current : region) {
    vector<Point> adj = current.adjacent();
    grid.drop_oob(adj);
    int perimeter = 4;
    for (const Point &point : adj) {
      if (grid.at(point) == grid.at(current)) {
        --perimeter;
      }
    }
    result += perimeter;
  }
  return result;
}

int solve_day12_pt1(const vector<string> &input) {
  unordered_set<Point, PointHash> visited;
  vector<unordered_set<Point, PointHash>> regions;
  Grid grid(input);
  for (size_t r = 0; r < input.size(); ++r) {
    for (size_t c = 0; c < input[0].size(); ++c) {
      const Point current = {static_cast<int>(r), static_cast<int>(c)};
      if (visited.find(current) != visited.end()) {
        continue;
      }
      regions.push_back(region(grid, visited, current));
    }
  }

  // cout << "visited = " << visited.size() << endl;
  assert(visited.size() == grid.width() * grid.height());

  int result = 0;
  for (const auto &region : regions) {
    int p = perimeter(region, grid);
    int a = region.size();
    int price = perimeter(region, grid) * region.size();
    result += price;
    cout << "region " << grid.at(*region.begin()) << " " << a << " * " << p
         << " = " << price << endl;
  }
  return result;
}

} // namespace Day12
