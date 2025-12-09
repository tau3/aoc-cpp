#include "day9.hpp"
#include "util.hpp"
#include <array>
#include <cassert>
#include <cstddef>
#include <string>
#include <vector>

namespace Day9 {

using Point = util::Point<long>;

long solve_day9_pt1(const vector<string> &input) {
  vector<Point> points;
  for (const string &line : input) {
    const vector<string> tokens = util::split(line, ",");
    Point point(stol(tokens[0]), stol(tokens[1]));
    points.push_back(point);
  }

  long result = 0;
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = i + 1; j < points.size(); j++) {
      const Point &left = points[i];
      const Point &right = points[j];
      if ((left.col == right.col) || (left.row == right.row)) {
        continue;
      }
      long area = abs(left.col - right.col + 1) * abs(left.row - right.row + 1);
      if (area > result) {
        result = area;
      }
    }
  }
  return result;
}

using Edge = pair<Point, Point>;

vector<Edge> to_edges(const vector<Point> &points) {
  vector<Point> queue = points;
  queue.push_back(queue[0]);

  vector<Edge> result;
  Point start = queue[0];
  while (!queue.empty()) {
    const Point &end = queue[queue.size() - 1];
    queue.pop_back();
    result.push_back({start, end});
    start = end;
  }
  assert(result.size() == (points.size() - 1));
  return result;
}

array<Point, 4> all_rectangle(const Point &left, const Point &right) {
  return {left, right, Point(left.row, right.col), Point(left.col, right.row)};
}

  bool is_crossing(const Edge &edge, const Point &point) {
    
  }

bool in_bounds(const vector<Edge> &edges, const Point &left,
               const Point &right) {
  const auto rectangle = all_rectangle(left, right);
  for (const Point &point : rectangle) {
    size_t count = 0;
    for (const Edge &edge : edges) {
      if (is_crossing(edge, point)) {
        count++;
      }
    }
    if ((count % 2) == 0) {
      return false;
    }
  }
  return true;
}

long solve_day9_pt2(const vector<string> &input) {
  vector<Point> points;
  for (const string &line : input) {
    const vector<string> tokens = util::split(line, ",");
    Point point(stol(tokens[0]), stol(tokens[1]));
    points.push_back(point);
  }

  const vector<Edge> edges = to_edges(points);
  long result = 0;
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = i + 1; j < points.size(); j++) {
      const Point &left = points[i];
      const Point &right = points[j];
      if ((left.col == right.col) || (left.row == right.row)) {
        continue;
      }
      if (!in_bounds(edges, left, right)) {
        continue;
      }
      long area = abs(left.col - right.col + 1) * abs(left.row - right.row + 1);
      if (area > result) {
        result = area;
      }
    }
  }
  return result;
}

} // namespace Day9
