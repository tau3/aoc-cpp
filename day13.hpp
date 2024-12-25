#ifndef INCLUDE_DAY_13_H
#define INCLUDE_DAY_13_H

#include <cstdint>
#include <string>
#include <vector>

namespace Day13 {

using namespace std;

struct Movement {
  uint64_t x;
  uint64_t y;
};

int64_t solve_arcade(const Movement &a_move, const Movement &b_move,
                      const Movement &prize);
int64_t solve_day13_pt1(const vector<string> &input);
int64_t solve_day13_pt2(const vector<string> &input);
} // namespace Day13

#endif
