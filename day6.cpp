#include "day6.hpp"
#include <array>
#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include <vector>

namespace Day6 {

string solve_day6(const vector<string> &input) {
  static const size_t width = 8;
  static const size_t english_letters = 26;

  array<array<size_t, english_letters>, width> indexes = {};

  for (const string &line : input) {
    for (size_t col = 0; col < width; col++) {
      const char i = line[col];
      const size_t j = i - 'a';
      indexes[col][j]++;
    }
  }

  string result = "";
  for (size_t i = 0; i < width; i++) {
    char current = 'a';
    size_t max = numeric_limits<size_t>::max();
    for (size_t j = 0; j < english_letters; j++) {
      if (indexes[i][j] < max) {
        max = indexes[i][j];
        current = j + 'a';
      }
    }
    result += current;
  }

  return result;
}

} // namespace Day6
