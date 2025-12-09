#include "day9.hpp"
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
  return {left, right, Point(left.row, right.col), Point(right.row, left.col)};
}

bool is_vertical(const Edge &edge) { return edge.first.col == edge.second.col; }

bool contains(const Edge &edge, const Point &point) {
  if (is_vertical(edge)) {
    if (edge.first.col != point.col) {
      return false;
    }
    const auto y1 = edge.first.row;
    const auto y2 = edge.second.row;
    const auto y = point.row;
    return ((y >= y1) && (y <= y2)) || ((y >= y2) && (y <= y1));
  } else {
    if (edge.first.row != point.row) {
      return false;
    }
    const auto x1 = edge.first.col;
    const auto x2 = edge.second.col;
    const auto x = point.col;
    return ((x >= x1) && (x <= x2)) || ((x >= x2) && (x <= x1));
  }
}

bool is_horizontal_crossing(const Edge &edge, const Point &point) {
  if (!is_vertical(edge)) {
    return edge.first.row == point.row;
  }

  Point intersection = Point(point.row, edge.first.col);
  return contains(edge, intersection);
}

bool is_in_area(const vector<Edge> &edges, const Point &point) {
  int i = 0;
  for (const Edge &edge : edges) {
    if (contains(edge, point)) {
      return true;
    }
    if (is_horizontal_crossing(edge, point)) {
      i++;
    }
  }
  cout << "[" << point.col << "," << point.row << "] has " << i << endl;
  return i % 2 != 0;
}

bool is_rectangle_in_bounds(const vector<Edge> &edges, const Point &left,
                            const Point &right) {
  // if (!(left.col == 9 && (left.row) == 5)) {
  //   return false;
  // }
  // if (!(right.col == 2 && (right.row) == 3)) {
  //   return false;
  // }
  // cout << "l=" << left.col << "," << left.row << endl;
  // cout << "r=" << right.col << "," << right.row << endl;

  const auto rectangle = all_rectangle(left, right);
  for (const Point &point : rectangle) {
    if (!is_in_area(edges, point)) {
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
      if (!is_rectangle_in_bounds(edges, left, right)) {
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
