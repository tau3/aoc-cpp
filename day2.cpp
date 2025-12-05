#include "day2.hpp"
#include "util.hpp"
#include <cassert>
#include <cstddef>
#include <string>
#include <vector>

namespace Day2 {

using namespace std;

long solve_day2_pt1(const vector<string> &input) {
  const string &line = input[0];
  long result = 0;
  for (const string &range : split(line, ",")) {
    const vector<string> tokens = split(range, "-");
    const long start = stol(tokens[0]);
    const long end = stol(tokens[1]);
    for (long i = start; i <= end; i++) {
      const string str_rep = to_string(i);
      const size_t length = str_rep.length();
      if ((length % 2) != 0) {
        continue;
      }
      const size_t half = length / 2;
      bool is_invalid = true;
      for (size_t j = 0; j < half; j++) {
        if (str_rep[j] != str_rep[j + half]) {
          is_invalid = false;
          break;
        }
      }
      if (is_invalid) {
        result += i;
      }
    }
  }
  return result;
}

vector<size_t> possible_pattern_lengths(const string &number) {
  vector<size_t> result;
  const size_t length = number.length();
  for (size_t i = 1; i <= length / 2; i++) {
    if (length % i == 0) {
      result.push_back(i);
    }
  }
  return result;
}

bool has_pattern(const string &number, const size_t step) {
  assert(step > 0);
  const size_t length = number.length();
  for (size_t i = 0; i < step; i++) {
    const char digit = number[i];
    for (size_t j = i + step; j < length; j += step) {
      if (number[j] != digit) {
        return false;
      }
    }
  }
  return true;
}

bool has_pattern(const long value) {
  const string str_rep = to_string(value);
  const vector<size_t> pattern_lengths = possible_pattern_lengths(str_rep);
  for (const size_t step : pattern_lengths) {
    if (has_pattern(str_rep, step)) {
      return true;
    }
  }
  return false;
}

long solve_day2_pt2(const vector<string> &input) {
  const string &line = input[0];
  long result = 0;
  for (const string &range : split(line, ",")) {
    const vector<string> tokens = split(range, "-");
    const long start = stol(tokens[0]);
    const long end = stol(tokens[1]);
    for (long i = start; i <= end; i++) {
      if (has_pattern(i)) {
        result += i;
      }
    }
  }
  return result;
}

} // namespace Day2
