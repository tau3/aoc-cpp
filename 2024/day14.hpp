#ifndef INCLUDE_DAY_14_H
#define INCLUDE_DAY_14_H

#include <string>
#include <vector>

namespace Day14 {

using namespace std;

struct Point {
  int x;
  int y;
};

using Grid = Point;

struct Robot {
  Point position;
  Point velocity;

  void move(const Grid &grid);
  int quadrant(const Grid &grid) const;
};

int solve_raw_input(const vector<string> &input, const Grid &grid);
int solve_pt2(const vector<string> &input, const Grid &grid);
} // namespace Day14

#endif
