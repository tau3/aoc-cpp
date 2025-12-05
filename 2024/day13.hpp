#ifndef INCLUDE_DAY_13_H
#define INCLUDE_DAY_13_H

#include <cstdint>
#include <string>
#include <vector>

namespace Day13 {

using namespace std;

using unit_t = int64_t;

struct Movement {
  unit_t x;
  unit_t y;
};

unit_t solve_arcade(const Movement &a_move, const Movement &b_move,
                      const Movement &prize);
unit_t solve_day13_pt1(const vector<string> &input);
unit_t solve_day13_pt2(const vector<string> &input);
} // namespace Day13

#endif
