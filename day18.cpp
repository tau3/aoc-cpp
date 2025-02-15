#include "util.hpp"
#include <cassert>
#include <cstddef>
#include <limits>
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

  const Point extract_min(vector<Point> &queue) const {
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

  vector<Point> adjacent(const Point &point) const {
    const auto [x, y] = point;
    vector<Point> all = {{x - 1, y}, {x + 1, y}, {x, y + 1}, {x, y - 1}};

    vector<Point> result;
    for (const Point &point : all) {
      if (contains(walls, point)) {
        continue;
      }

      if ((point.x >= 0) && (point.y >= 0) && (point.x <= target.x) &&
          (point.y <= target.y)) {
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
          distances[point] = numeric_limits<int>::max();
          queue.push_back(point);
        }
      }
    }
    distances[{0, 0}] = 0;

    while (!queue.empty()) {
      const Point &u = extract_min(queue);
      for (const Point &v : adjacent(u)) {
        const int candidate = distances[u] + 1;
        if (distances[v] > candidate) {
          distances[v] = candidate;
        }
      }
    }

    return distances[target];
  }
};

int solve(const vector<Point> &bytes, const Point &end) {
  Solver solver(bytes, end);
  int result = solver.dijcstra();
  return result;
}

Point convert_to_point(const vector<string> &input, const size_t index) {
  const string &line = input[index];
  const auto tokens = split(line, ",");
  return {stoi(tokens[0]), stoi(tokens[1])};
}

vector<Point> bytes_up_to(const vector<string> &input, const size_t limit) {
  vector<Point> bytes;
  for (size_t i = 0; i < limit; ++i) {
    bytes.push_back(convert_to_point(input, i));
  }
  return bytes;
}

int solve_day18_pt1(const vector<string> &input, const Point &end,
                    const size_t limit) {
  return solve(bytes_up_to(input, limit), end);
}

string solve_day18_pt2(const vector<string> &input, const Point &end,
                       const size_t limit) {
  size_t l = limit;
  size_t r = input.size() - 1;
  while (l <= r) {
    const size_t m = (l + r) / 2;
    const int solution = solve(bytes_up_to(input, m), end);
    if (solution < 0) {
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  return input[r];
}

} // namespace Day18
