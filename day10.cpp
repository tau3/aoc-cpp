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

} // namespace Day10
