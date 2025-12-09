#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "util.hpp"

namespace geometry {

using Point = util::Point<long>;

struct Line {
  double a;
  double b;
  double c;

  explicit Line(double a, double b, double c) : a(a), b(b), c(c) {}
};

bool intersect(const Line &, const Line &, Point &res);

Line segment_to_line(const Point &, const Point &);

} // namespace geometry

#endif
