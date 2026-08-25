#include "day3.hpp"
#include "util.hpp"

namespace Day3 {

size_t solve_day3_pt1(const vector<string> &input) {
  size_t result = 0;
  for (const string &line : input) {
    const vector<string> tokens = util::split_by_spaces(line);
    const int a = stoi(tokens[0]);
    const int b = stoi(tokens[1]);
    const int c = stoi(tokens[2]);

    if ((a < (b + c)) && (b < (a + c)) && (c < (a + b))) {
      result++;
    }
  }
  return result;
}

} // namespace Day3
