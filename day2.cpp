#include "day2.hpp"
#include "util.hpp"
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <vector>

namespace Day2 {

using namespace std;

int solve_pt1(const vector<string> &input) {
  int result = 0;

  for (const string &line : input) {
    const vector<string> tokens = util::split_by_spaces(line);
    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();
    for (const string &token : tokens) {
      const int num = stoi(token);
      if (num < min) {
        min = num;
      }
      if (num > max) {
        max = num;
      }
    }
    const int diff = max - min;
    result += diff;
  }

  return result;
}

int find_num(const vector<int> &nums) {
  for (size_t i = 0; i < nums.size(); i++) {
    for (size_t j = i + 1; j < nums.size(); j++) {
      const int left = nums[i];
      const int right = nums[j];
      if ((left > right) && (left % right == 0)) {
        return left / right;
      }
      if ((right > left) && (right % left == 0)) {
        return right / left;
      }
    }
  }
  throw runtime_error("unreachable");
}

int solve_pt2(const vector<string> &input) {
  int result = 0;

  for (const string &line : input) {
    const vector<string> tokens = util::split_by_spaces(line);
    vector<int> nums;
    for (const string &token : tokens) {
      const int num = stoi(token);
      nums.push_back(num);
    }
    result += find_num(nums);
  }
  return result;
}

} // namespace Day2
