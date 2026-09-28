#include "day18.hpp"
#include <cstddef>

namespace Day18 {

bool is_trap(const char left, const char center, const char right) {
  if ((left == '^') && (center == '^') && (right == '.')) {
    return true;
  }

  if ((left == '.') && (center == '^') && (right == '^')) {
    return true;
  }

  if ((left == '^') && (center == '.') && (right == '.')) {
    return true;
  }

  if ((left == '.') && (center == '.') && (right == '^')) {
    return true;
  }

  return false;
}

// TODO booleans?
string build_next_row(const string &row) {
  string result;

  for (size_t i = 0; i < row.size(); i++) {
    const char left = (i == 0) ? '.' : row[i - 1];
    const char center = row[i];
    const char right = (i == (row.size() - 1)) ? '.' : row[i + 1];

    result += is_trap(left, center, right) ? '^' : '.';
  }

  return result;
}

size_t solve(string input, const size_t rows) {
  size_t result = 0;
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < input.size(); j++) {
      if (input[j] == '.') {
        result++;
      }
    }

    input = build_next_row(input);
  }
  return result;
}

} // namespace Day18
