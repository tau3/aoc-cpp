#include "util.hpp"
#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

namespace Day18 {

using namespace std;

struct Point {
  int x;
  int y;
};

bool operator==(const Point &lhs, const Point &rhs) {
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

struct PointHash {
  size_t operator()(const Point &point) const {
    const auto [r, c] = point;
    return 31 * r + 17 * c;
  }
};

class Solver {
  unordered_map<Point, int, PointHash> distances;
  vector<Point> walls;
  Point target;

  Solver() {};

  const Point &exract_min(vector<Point> &queue) const {
    assert(!queue.empty());

    Point &result = queue[0];
    int distance = distances.at(result);
    size_t index = 0;
    for (size_t i = 1; i < queue.size(); ++i) {
      const Point &current = queue[i];
      const int candidate = distances.at(current);
      if (candidate < distance) {
        result = current;
        distance = candidate;
        index = i;
      }
    }

    queue.erase(queue.begin() + index);
    return result;
  }

  vector<Point> adjacent(const Point &point) const {
    const auto [x, y] = point;
    vector<Point> result;
    if (x > 0) {
      const Point point{x - 1, y};
      if (!contains(walls, point)) {
        result.push_back(point);
      }
    }
    if (x < target.x - 1) {
      const Point point{x + 1, y};
      if (!contains(walls, point)) {
        result.push_back(point);
      }
    }
    if (y > 0) {
      const Point point({x, y - 1});
      if (!contains(walls, point)) {
        result.push_back(point);
      }
    }

    if (y < target.y - 1) {
      const Point point{x, y + 1};
      if (!contains(walls, point)) {
        result.push_back(point);
      }
    }
    return result;
  }

public:
  Solver(const vector<Point> walls, const Point target)
      : walls(walls), target(target) {}

  int dijcstra() {
    vector<Point> queue;
    for (int x = 0; x <= target.x; ++x) {
      for (int y = 0; y <= target.y; ++y) {
        const Point point{x, y};
        if (!contains(walls, point)) {
          distances[point] = 0;
          queue.push_back(point);
        }
      }
    }
    distances[{0, 0}] = 0;

    while (!queue.empty()) {
      const Point &u = exract_min(queue);
      for (const Point &v : adjacent(u)) {
        if (distances[v] > distances[u] + 1) {
          distances[v] = distances[u] + 1;
        }
      }
    }

    return distances[target];
  }
};

int solve(const vector<Point> &bytes, const Point &end) {
  Solver solver(bytes, end);
  return solver.dijcstra();
}

int solve_day18_pt1(const vector<string> &input, const Point &end,
                    const size_t limit) {
  vector<Point> bytes;
  for (size_t i = 0; i < limit; ++i) {
    const string &line = input[i];
    const auto tokens = split(line, ",");
    bytes.push_back({stoi(tokens[0]), stoi(tokens[1])});
  }

  return solve(bytes, end);
}

} // namespace Day18
