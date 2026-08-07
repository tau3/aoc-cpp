#include "day16.hpp"
#include "util.hpp"
#include <stdexcept>
#include <unordered_map>

namespace Day16 {

// clang-format off
const std::unordered_map<std::string, int> EXPECTED = {
    {"children", 3},
    {"cats", 7},
    {"samoyeds", 2},
    {"pomeranians", 3},
    {"akitas", 0},
    {"vizslas", 0},
    {"goldfish", 5},
    {"trees", 3},
    {"cars", 2},
    {"perfumes", 1}
};
// clang-format on

bool matches(const std::vector<std::string> &tokens, const size_t key_index) {
  std::string key = tokens[key_index];
  key.pop_back();

  std::string value = tokens[key_index + 1];
  if (value[value.size() - 1] == ',') {
    value.pop_back();
  }
  int actual = std::stoi(value);
  int expected = EXPECTED.at(key);
  return expected == actual;
}

bool matches2(const std::vector<std::string> &tokens, const size_t key_index) {
  std::string key = tokens[key_index];
  key.pop_back();

  std::string value = tokens[key_index + 1];
  if (value[value.size() - 1] == ',') {
    value.pop_back();
  }

  int actual = std::stoi(value);
  int expected = EXPECTED.at(key);

  if (key == "cats" || key == "trees") {
    return actual > expected;
  } else if (key == "pomeranians" || key == "goldfish") {
    return actual < expected;
  }

  return expected == actual;
}

int solve(const std::vector<std::string> &input, const bool pt2) {
  for (const std::string &line : input) {
    const std::vector<std::string> tokens = util::split(line, " ");
    const bool found =
        pt2 ? matches2(tokens, 2) && matches2(tokens, 4) && matches2(tokens, 6)
            : matches(tokens, 2) && matches(tokens, 4) && matches(tokens, 6);
    if (found) {
      std::string result = tokens[1];
      result.pop_back();
      return std::stoi(result);
    }
  }
  throw std::runtime_error("unreachable");
}

int solve_day16_pt1(const std::vector<std::string> &input) {
  return solve(input, false);
}

int solve_day16_pt2(const std::vector<std::string> &input) {
  return solve(input, true);
}

} // namespace Day16
