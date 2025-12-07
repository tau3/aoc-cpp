#include "day6.hpp"
#include "util.hpp"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace Day6 {

void check_sizes(const vector<vector<string>> &tokenized) {
  const size_t a = tokenized[0].size();
  const size_t b = tokenized[1].size();
  const size_t c = tokenized[2].size();
  const size_t d = tokenized[3].size();
  assert((a == b) && (a == c) && (a == d));
}
uint64_t solve_day6_pt1(const vector<string> &input) {
  vector<vector<string>> tokenized;
  for (const string &line : input) {
    vector<string> tokens = util::split_by_spaces(line);
    tokenized.push_back(tokens);
  };
  check_sizes(tokenized);
  uint64_t result = 0;
  for (size_t i = 0; i < tokenized[0].size(); i++) {
    uint64_t a = stoi(tokenized[0][i]);
    uint64_t b = stoi(tokenized[1][i]);
    uint64_t c = stoi(tokenized[2][i]);
    if (tokenized[3][i] == "+") {
      result += (a + b + c);
    } else {
      result += (a * b * c);
    }
  }
  return result;
}

} // namespace Day6
