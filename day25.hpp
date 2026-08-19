#ifndef INCLUDE_DAY_25_H
#define INCLUDE_DAY_25_H

#include <cstddef>
#include <cstdint>
#include <functional>

namespace Day25 {

uint64_t iterate(const size_t row, const size_t column, const uint64_t start,
                 const std::function<uint64_t(const uint64_t)> &next);
uint64_t solve_day25_pt1(const size_t row, const size_t column);

} // namespace Day25

#endif
