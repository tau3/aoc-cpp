// http://e-maxx.ru/algo/lines_intersection
#include "geometry.hpp"
#include <cstdlib>

namespace geometry {

const double EPS = 1e-9;

double det(const double a, const double b, const double c, const double d) {
  return a * d - b * c;
}

bool intersect(const Line &m, const Line &n, Point &res) {
  double zn = det(m.a, m.b, n.a, n.b);
  if (abs(zn) < EPS)
    return false;
  res.col = -det(m.c, m.b, n.c, n.b) / zn;
  res.row = -det(m.a, m.c, n.a, n.c) / zn;
  return true;
}

Line segment_to_line(const Point &p, const Point &q) {
  const double a = p.row - q.row;
  const double b = q.col - p.col;
  const double c = -a * p.col - b * p.row;
  return Line(a, b, c);
}

} // namespace geometry
