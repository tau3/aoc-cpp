#include "day25.hpp"
#include <cstddef>
#include <cstdint>

namespace Day25 {

uint64_t iterate(const size_t row, const size_t column, const uint64_t start,
                 const std::function<uint64_t(const uint64_t)> &next) {
  size_t r = 1;
  size_t c_max = 1;
  size_t c = 1;
  uint64_t num = start;

  while ((r != row) || (c != column)) {
    if (c == c_max) {
      c = 1;
      c_max++;
      r = c_max;
      num = next(num);
    } else {
      c++;
      r--;
      num = next(num);
    }
  }

  return num;
}

uint64_t solve_day25_pt1(const size_t row, const size_t column) {
  return iterate(row, column, 20151125, [](const uint64_t x) -> uint64_t {
    return (x * 252533) % 33554393;
  });
}

} // namespace Day25
