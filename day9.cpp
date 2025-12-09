#include "day9.hpp"
#include "geometry.hpp"
#include "util.hpp"
#include <array>
#include <cassert>
#include <cmath>
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
  Point start = queue[queue.size() - 1];
  queue.pop_back();
  while (!queue.empty()) {
    const Point &end = queue[queue.size() - 1];
    queue.pop_back();
    result.push_back({start, end});
    start = end;
  }
  assert(result.size() == (points.size()));
  return result;
}

array<Point, 4> all_rectangle(const Point &left, const Point &right) {
  return {left, right, Point(left.row, right.col), Point(left.col, right.row)};
}

double euclid(const Point &left, const Point &right) {
  return sqrt((left.col - right.col) * (left.col - right.col) +
              (left.row - right.row) * (left.row - right.row));
}

bool contains(const Edge &edge, const Point &point) {
  return euclid(edge.first, point) + euclid(edge.second, point) ==
         euclid(edge.first, edge.second);
}

bool is_crossing(const Edge &edge, const Point &point) {
  geometry::pt left;
  geometry::pt right;
  const bool is_intersect_lines = geometry::intersect(
      {static_cast<double>(edge.first.col),
       static_cast<double>(edge.first.row)},
      {static_cast<double>(edge.second.col),
       static_cast<double>(edge.second.row)},
      {static_cast<double>(point.col), static_cast<double>(point.row)},
      {static_cast<double>(point.col + 1), static_cast<double>(point.row - 1)},
      left, right);
  if (!is_intersect_lines) {
    return false;
  }

  const Point intersection_point = Point(left.y, left.x);
  return contains(edge, intersection_point);
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
    Point point(stol(tokens[1]), stol(tokens[0]));
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
