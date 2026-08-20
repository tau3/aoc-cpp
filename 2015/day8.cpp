#include "day8.hpp"
#include <cstddef>
#include <iostream>

namespace Day8 {

size_t solve_line(const string &line) {
  const size_t length = line.size();
  size_t result = length - 2;
  for (size_t i = 0; i < length; i++) {
    if (line[i] == '\\') {
      if (line[i + 1] == 'x') {
        result -= 3;
        i += 3;
      } else {
        result--;
        i += 2;
      }
    }
  }
  // cout << "l=" << line << "; len=" << length << "; r=" << result << endl;
  return length - result;
}

size_t solve_day8_pt1(const vector<string> &input) {
  size_t result = 0;
  for (const string &line : input) {
    result += solve_line(line);
  }
  return result;
}

} // namespace Day8
