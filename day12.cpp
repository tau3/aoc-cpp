#include "day14.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

struct Point {
  int r;
  int c;

  vector<Point> adjacent(const Grid &grid) const {
    vector<Point> result = {{r - 1, c}, {r, c + 1}, {r + 1, c}, {r, c - 1}};
    result.erase(
        remove_if(result.begin(), result.end(), [&grid](const Point &point) {
          return (point.c < 0) || (point.r < 0) || (point.c >= grid.width()) ||
                 (point.r >= grid.height());
        }));
    return result;
  }
};

class Grid {
  vector<string> grid;

  Grid() {};

public:
  Grid(vector<string> grid) : grid(grid) {};

  char at(const Point &point) const { return grid[point.r][point.c]; }

  size_t width() const { return grid[0].size(); }

  size_t height() const { return grid.size(); }
};

unordered_set<Point> expand_region(const Point &start, const Grid &grid,
                                   unordered_set<Point> &visited) {
  unordered_set<Point> region = {start};
  const auto adjacent = start.adjacent(grid);
  for (const Point &point : adjacent) {
    if (visited.find(point) != visited.end()) {
      continue;
    }
    if (grid.at(point) == grid.at(start)) {
      region.insert(point);
      visited.insert(point);
      region.insert(expand_region(point, grid, visited));
    }
  }
  return region;
}

int solve(const vector<string> &input) {
  vector<unordered_set<Point>> regions;
  unordered_set<Point> visited;
  Grid grid(input);
  for (size_t r = 0; r < input.size(); ++r) {
    for (size_t c = 0; c < input[0].size(); ++c) {
      const Point point = {r, c};
      if (const auto &[_, seen] = visited.insert(point); seen) {
        continue;
      }
      regions.push_back(expand_region(point, grid, visited));
    }
  }

  assert(visited.size() == grid.height() * grid.width());

  int result = 0;
  for(const unordered_set<Point>& region: regions){
    result += region.size();
  }
  return result;
}
