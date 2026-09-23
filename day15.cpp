#include "day15.hpp"

namespace Day15 {

int solve_pt1(const vector<pair<int, int>> &disks) {
  int i = 1;
  while (true) {
    bool is_found = true;
    for (const auto &[width, start] : disks) {
      const bool at_start = ((start + i + 1) % width) == 0;
      if (!at_start) {
        is_found = false;
        break;
      }
    }

    if (is_found) {
      return i;
    }

    i++;
  }
}

} // namespace Day15
