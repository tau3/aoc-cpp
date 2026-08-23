#include "day2.hpp"
#include <format>
#include <stdexcept>

namespace Day2 {

int move(const int current, const char direction) {
  switch (direction) {
  case 'U':
    if (current == 1 || current == 2 || current == 3) {
      return current;
    } else {
      return current - 3;
    }
    break;
  case 'L':
    if (current == 1 || current == 4 || current == 7) {
      return current;
    } else {
      return current - 1;
    }
    break;
  case 'R':
    if (current == 3 || current == 6 || current == 9) {
      return current;
    } else {
      return current + 1;
    }
    break;
  case 'D':
    if (current == 7 || current == 8 || current == 9) {
      return current;
    } else {
      return current + 3;
    }
    break;
  }
  throw std::runtime_error(std::format("invalid direction: {}", direction));
}

std::string solve_day2_pt1(const std::vector<std::string> &input) {
  std::string result = "";
  int current = 5;
  for (const std::string &line : input) {
    for (const char letter : line) {
      current = move(current, letter);
    }
    result += std::to_string(current);
  }
  return result;
}

} // namespace Day2
