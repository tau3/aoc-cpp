#include "day3.hpp"
#include "util.hpp"
#include <array>
#include <cassert>
#include <cstddef>
#include <vector>

namespace Day3 {

bool is_triangle(const int a, const int b, const int c) {
  return (a < (b + c)) && (b < (a + c)) && (c < (a + b));
}

size_t solve_day3_pt1(const vector<string> &input) {
  size_t result = 0;
  for (const string &line : input) {
    const vector<string> tokens = util::split_by_spaces(line);
    const int a = stoi(tokens[0]);
    const int b = stoi(tokens[1]);
    const int c = stoi(tokens[2]);

    if (is_triangle(a, b, c)) {
      result++;
    }
  }
  return result;
}

const static int BLOCK_SIZE = 9;

size_t count_triangles(const array<int, BLOCK_SIZE> &nums) {
  assert(nums.size() == BLOCK_SIZE);

  return is_triangle(nums[0], nums[3], nums[6]) +
         is_triangle(nums[1], nums[4], nums[7]) +
         is_triangle(nums[2], nums[5], nums[8]);
}

size_t solve_day3_pt2(const vector<string> &input) {
  size_t result = 0;
  size_t i = 0;
  array<int, BLOCK_SIZE> buffer;
  for (const string &line : input) {
    const vector<string> tokens = util::split_by_spaces(line);
    buffer[i++] = stoi(tokens[0]);
    buffer[i++] = stoi(tokens[1]);
    buffer[i++] = stoi(tokens[2]);

    if (i == BLOCK_SIZE) {
      result += count_triangles(buffer);
      i = 0;
    }
  }
  return result;
}

} // namespace Day3
