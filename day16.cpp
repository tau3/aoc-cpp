#include "day16.hpp"
#include <cassert>
#include <cstddef>

namespace Day16 {

void generate_step(string &line) {
  const size_t length = line.size();
  line += '0';
  for (size_t i = 0; i < length; i++) {
    if (line[i] == '0') {
      line += '1';
    } else {
      line += '0';
    }
  }
}

string checksum(const string &line) {
  assert(line.size() % 2 == 0);

  const size_t half = line.size() / 2;

  string result = 0;
  for (size_t i = 0; i < half; i++) {
    const size_t j = i * 2;
    const char l = line[j];
    const char r = line[j + 1];
    if (l == r) {
      result += '1';
    } else {
      result += '0';
    }
  }

  return result;
}

string solve_pt1(string &input, const size_t length) {
  while (input.size() < length) {
    generate_step(input);
  }

  input.resize(length);

  do {
    input = checksum(input);
  } while (input.length() % 2 != 0);

  return input;
}

} // namespace Day16
