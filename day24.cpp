#include "day24.hpp"
#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>

namespace Day24 {

uint64_t calc_product(const vector<uint64_t> &numbers) {
  uint64_t result = 1;
  for (const uint64_t number : numbers) {
    result *= number;
  }
  return result;
}

uint64_t calc_sum(const vector<uint64_t> &numbers) {
  uint64_t result = 1;
  for (const uint64_t number : numbers) {
    result += number;
  }
  return result;
}

uint64_t calc_min_product(const vector<vector<uint64_t>> &candidates) {
  uint64_t result = numeric_limits<uint64_t>::max();
  for (const vector<uint64_t> &combination : candidates) {
    const uint64_t product = calc_product(combination);
    if (product < result) {
      result = product;
    }
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
  const size_t input_size = numbers.size();
  const uint64_t all = 1 << input_size;
  size_t min_size = input_size;
  for (uint64_t i = 1; i < all; i++) {
    vector<uint64_t> combination;
    for (size_t j = 0; j < input_size; j++) {
      if (i & (1 << j)) {
        combination.push_back(numbers[j]);
      }
    }

    uint64_t combination_sum = calc_sum(combination);
    if (combination_sum == group_sum) {
      const size_t size = combination.size();
      if (size == min_size) {
        candidates.push_back(combination);
      } else if (size < min_size) {
        min_size = size;
        candidates = {combination};
      }
    }
  }

  return calc_min_product(candidates);
}

uint64_t solve_day24_pt1(const vector<string> &input) {
  return solve(input, 3);
}

uint64_t solve_day24_pt2(const vector<string> &input) {
  return solve(input, 4);
}

} // namespace Day24
