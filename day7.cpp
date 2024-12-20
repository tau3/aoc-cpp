#include "day7.hpp"
#include "util.hpp"
#include <queue>
#include <string>

namespace Day7 {

target_t concat(const target_t lhs, const target_t rhs) {
  string result = to_string(lhs);
  result += to_string(rhs);
  return stol(result);
}

bool can_produce(const target_t target, queue<target_t> &nums,
                 const bool is_use_concat) {
  const target_t first = nums.front();
  nums.pop();

  const target_t second = nums.front();
  nums.pop();

  vector<target_t> memo = {first * second, first + second};
  if (is_use_concat) {
    memo.push_back(concat(first, second));
  }

  while (!nums.empty()) {
    vector<target_t> new_memo;
    new_memo.reserve(memo.size() * 2);

    const target_t current = nums.front();
    nums.pop();

    for (const target_t val : memo) {
      const target_t mul = val * current;
      const target_t sum = val + current;
      new_memo.push_back(mul);
      new_memo.push_back(sum);

      if (is_use_concat) {
        const target_t cct = concat(val, current);
        new_memo.push_back(cct);
      }
    }

    memo = new_memo;
  }

  for (const target_t result : memo) {
    if (result == target) {
      return true;
    }
  }
  return false;
}

pair<target_t, queue<target_t>> parse(const string &line) {
  const vector<string> tokens = split(line, " ");

  string target_str = tokens[0];
  target_str = target_str.substr(0, target_str.size() - 1);

  const target_t target = stol(target_str);

  queue<target_t> nums;
  for (size_t i = 1; i < tokens.size(); ++i) {
    nums.push(stoi(tokens[i]));
  }

  return {target, nums};
}

target_t solve(const vector<string> &input, const bool is_use_concat) {
  target_t result = 0;
  for (const string &line : input) {
    auto [target, nums] = parse(line);
    if (can_produce(target, nums, is_use_concat)) {
      result += target;
    }
  }
  return result;
}

target_t solve_day7_pt1(const vector<string> &input) {
  return solve(input, false);
}

target_t solve_day7_pt2(const vector<string> &input) {
  return solve(input, true);
}
} // namespace Day7
