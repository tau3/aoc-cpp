#include "day3.hpp"
#include "util.hpp"
#include <cctype>
#include <cstddef>
#include <regex>
#include <string>

// mul(123,4)
int calc_single_mul(const string &input) {
  std::regex mul("mul\\(([0-9]{1,3}),([0-9]{1,3})\\).*");
  std::smatch pieces_match;
  if (!std::regex_match(input, pieces_match, mul)) {
    return 0;
  }
  int left = stoi(pieces_match[1]);
  int right = stoi(pieces_match[2]);
  return left * right;
}

int solve(string input) {
  int result = 0;
  size_t loc = input.find("mul(", 0);
  while (loc < input.size()) {
    input = input.substr(loc);
    result += calc_single_mul(input);
    input = input.substr(4);
    loc = input.find("mul(", 0);
  }
  return result;
}
