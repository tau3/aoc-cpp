#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cstdlib>

namespace geometry {

const double EPS = 1E-9;

struct pt {
  double x, y;

  bool operator<(const pt &p) const {
    return x < p.x - EPS || abs(x - p.x) < EPS && y < p.y - EPS;
  }
};

bool intersect(pt a, pt b, pt c, pt d, pt &left, pt &right);

} // namespace geometry

#endif
