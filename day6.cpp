#include "day6.hpp"
#include "util.hpp"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace Day6 {

uint64_t solve_day6_pt1(const vector<string> &input) {
  vector<vector<string>> tokenized;
  for (const string &line : input) {
    vector<string> tokens = util::split_by_spaces(line);
    tokenized.push_back(tokens);
  };
  uint64_t result = 0;
  for (size_t i = 0; i < tokenized[0].size(); i++) {
    const string operation = tokenized[tokenized.size() - 1][i];
    uint64_t subresult = (operation == "+") ? 0 : 1;
    for (size_t j = 0; j < tokenized.size() - 1; j++) {
      const uint64_t num = stoi(tokenized[j][i]);
      subresult = (operation == "+") ? (subresult + num) : (subresult * num);
    }
    result += subresult;
  }
  return result;
}

} // namespace Day6
