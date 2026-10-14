#include "day7.hpp"

namespace Day7 {

bool has_abba(const string &line) {
  for (size_t i = 0; i < line.size() - 3; i++) {
    if ((line[i] != line[i + 1]) && (line[i] == line[i + 3]) &&
        (line[i + 1] == line[i + 2])) {
      return true;
    }
  }
  return false;
}

bool is_tls(const string &address) {
  string left;
  string middle;
  string right;
  string *current = &left;

  for (const char c : address) {
    if (c == '[') {
      current = &middle;
      continue;
    }
    if (c == ']') {
      current = &right;
      continue;
    }

    *current += c;
  }

  return !has_abba(middle) && (has_abba(left) || has_abba(right));
}

size_t solve_day7_pt1(const vector<string> &input) {
  size_t result = 0;
  for (const string &line : input) {
    if (is_tls(line)) {
      result++;
    }
  }
  return result;
}

} // namespace Day7
