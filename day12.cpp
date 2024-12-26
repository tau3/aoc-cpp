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

  vector<Point> adjacent() const {
    return {{r - 1, c}, {r, c + 1}, {r + 1, c}, {r, c - 1}};
  }
};

struct PointHash {
  size_t operator()(const Point &point) const {
    const auto [r, c] = point;
    return 31 * r + 17 * c;
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

  void drop_oob(vector<Point>& points) const {
    points.erase(
        remove_if(points.begin(), points.end(), [this](const Point &point) {
          return (point.c < 0) || (point.r < 0) || (point.c >= width()) ||
                 (point.r >= height());
        }));
  }
};

void add_all(unordered_set<Point, PointHash> &lhs,
             const unordered_set<Point, PointHash> rhs) {
  for(const Point& point:rhs){
    lhs.insert(point);
  }
}

unordered_set<Point, PointHash> expand_region(const Point &start, const Grid &grid,
					      unordered_set<Point, PointHash> &visited) {
  unordered_set<Point, PointHash> region = {start};
  const auto adjacent = start.adjacent();
  for (const Point &point : adjacent) {
    if (visited.find(point) != visited.end()) {
      continue;
    }
    if (grid.at(point) == grid.at(start)) {
      region.insert(point);
      visited.insert(point);
      add_all(region, expand_region(point, grid, visited));
    }
  }
  return region;
}

int solve(const vector<string> &input) {
  vector<unordered_set<Point, PointHash>> regions;
  unordered_set<Point, PointHash> visited;
  Grid grid(input);
  for (size_t r = 0; r < input.size(); ++r) {
    for (size_t c = 0; c < input[0].size(); ++c) {
      const Point point = {static_cast<int>(r), static_cast<int>(c)};
      if (const auto &[_, seen] = visited.insert(point); seen) {
        continue;
      }
      regions.push_back(expand_region(point, grid, visited));
    }
  }

  assert(visited.size() == grid.height() * grid.width());

  int result = 0;
  for(const unordered_set<Point, PointHash>& region: regions){
    result += region.size();
  }
  return result;
}
