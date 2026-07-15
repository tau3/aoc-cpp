#include <cassert>
#include <cstddef>
#include <string>

namespace Day10 {

std::string look_and_say_step(const std::string &input) {
  assert(input.length() > 0);
  char current = input[0];
  size_t count = 1;
  std::string result = "";
  for (size_t i = 1; i < input.length(); i++) {
    if (input[i] == current) {
      count++;
    } else {
      result += std::to_string(count);
      result += current;
      count = 1;
      current = input[i];
    }
  }
  result += std::to_string(count);
  result += current;
  return result;
}

size_t solve_day10_pt1(const std::string &input) {
  std::string result = input;
  for (int i = 0; i < 40; i++) {
    result = look_and_say_step(result);
  }
  return result.length();
}

size_t solve_day10_pt2(const std::string &input) {
  std::string result = input;
  for (int i = 0; i < 50; i++) {
    result = look_and_say_step(result);
  }
  return result.length();
}

} // namespace Day10
