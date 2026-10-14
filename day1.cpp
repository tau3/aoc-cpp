#include "day1.hpp"
#include <cstddef>

namespace Day1 {

int solve_pt1(const std::string &input) {
  int result = 0;

  const size_t size = input.size();
  for (size_t i = 0; i < size; i++) {
    const size_t next_index = (i + 1) % size;

    const char current = input[i];
    const char next = input[next_index];
    if (current == next) {
      result += (current - '0');
    }
  }
  return result;
}

int solve_pt2(const std::string &input) {
  int result = 0;

  const size_t size = input.size();
  const size_t half = size / 2;
  for (size_t i = 0; i < size; i++) {
    const size_t next_index = (i + half) % size;

    const char current = input[i];
    const char next = input[next_index];
    if (current == next) {
      result += (current - '0');
    }
  }
  return result;
}

} // namespace Day1
