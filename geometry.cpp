// http://e-maxx.ru/algo/lines_intersection

#include <cstdlib>
struct pt {
  double x, y;
};

struct line {
  double a, b, c;
};

const double EPS = 1e-9;

double det(double a, double b, double c, double d) { return a * d - b * c; }

bool intersect(line m, line n, pt &res) {
  double zn = det(m.a, m.b, n.a, n.b);
  if (abs(zn) < EPS)
    return false;
  res.x = -det(m.c, m.b, n.c, n.b) / zn;
  res.y = -det(m.a, m.c, n.a, n.c) / zn;
  return true;
}
