#include "day9.hpp"
#include <cstddef>
#include <iostream>

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
  string prefix = "";
  string suffix = "";
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
      continue;
    };

    switch (state) {
    case State::NONE:
      result += c;
      break;
    case State::MARKER_PREFIX:
      prefix += c;
      break;
    case State::MARKER_SUFFIX:
      suffix += c;
      break;
    case State::MARKER_EXIT:
      const size_t subsequent = stol(prefix);
      const size_t repeats = stol(suffix);
      const string repeated = str.substr(i, subsequent);
      cout << "repeated=" << repeated << ", repeats=" << repeats << endl;
      repeat(result, repeated, repeats);
      suffix = "";
      prefix = "";
      i += subsequent - 1;
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
