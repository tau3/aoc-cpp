#include "day24.hpp"
#include <cstdint>
#include <limits>

namespace Day24 {

uint64_t calc_product(const vector<uint64_t> &numbers) {
  uint64_t result = 1;
  for (const uint64_t number : numbers) {
    result *= number;
  }
  return result;
}

uint64_t solve(const vector<string> &input, const int count) {
  vector<uint64_t> numbers;
  uint64_t sum = 0;
  for (const string &line : input) {
    const uint64_t number = stoi(line);
    numbers.push_back(number);
    sum += number;
  }

  const uint64_t group_sum = sum / count;

  vector<vector<uint64_t>> candidates;
  size_t min_length = numbers.size();
  const uint64_t all = 1 << numbers.size();
  for (uint64_t i = 1; i < all; i++) {
    vector<uint64_t> combination;
    for (size_t j = 0; j < numbers.size(); j++) {
      if (i & (1 << j)) {
        combination.push_back(numbers[j]);
      }
    }

    uint64_t combination_sum = 0;
    for (const uint64_t j : combination) {
      combination_sum += j;
    }
    if (combination_sum == group_sum) {
      if (combination.size() == min_length) {
        candidates.push_back(combination);
      } else if (combination.size() < min_length) {
        min_length = combination.size();
        candidates.clear();
        candidates.push_back(combination);
      }
    }
  }

  uint64_t result = numeric_limits<uint64_t>::max();
  for (const vector<uint64_t> &combination : candidates) {
    const uint64_t product = calc_product(combination);
    if (product < result) {
      result = product;
    }
  }

  return result;
}

uint64_t solve_day24_pt1(const vector<string> &input) {
  return solve(input, 3);
}

uint64_t solve_day24_pt2(const vector<string> &input) {
  return solve(input, 4);
}

} // namespace Day24
