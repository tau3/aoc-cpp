#include "day9.hpp"
#include <cstddef>

namespace Day9 {

enum class State {
  NONE,
  MARKER_PREFIX,
  MARKER_SUFFIX,
  MARKER_EXIT,
};

void repeat(string &prefix, const string &suffix, const size_t count);

string decompress(const string &str) {
  State state = State::NONE;
  string result = "";
  size_t repeated_size = 0;
  size_t repeats_count = 0;
  for (size_t i = 0; i < str.size(); i++) {
    const char c = str[i];
    switch (c) {
    case '(':
      state = State::MARKER_PREFIX;
      continue;
    case 'x':
      state = State::MARKER_SUFFIX;
      continue;
    case ')':
      state = State::MARKER_EXIT;
      i++;
      break;
    };

    switch (state) {
    case State::NONE:
      result += c;
      break;
    case State::MARKER_PREFIX:
      repeated_size *= 10;
      repeated_size += (c - '0');
      break;
    case State::MARKER_SUFFIX:
      repeats_count *= 10;
      repeats_count += (c - '0');
      break;
    case State::MARKER_EXIT:
      const string repeated_line = str.substr(i, repeated_size);
      repeat(result, repeated_line, repeats_count);
      repeats_count = 0;
      repeated_size = 0;
      i += repeated_size - 1;
      state = State::NONE;
      break;
    }
  }
  return result;
}

void repeat(string &prefix, const string &suffix, const size_t count) {
  for (size_t i = 0; i < count; i++) {
    prefix += suffix;
  }
}

} // namespace Day9
