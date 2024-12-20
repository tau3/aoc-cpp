#include "day7.hpp"
#include "util.hpp"
#include <queue>

namespace Day7 {

bool can_produce(int target, queue<int> &nums) {
  int first = nums.front();
  nums.pop();

  int second = nums.front();
  nums.pop();

  vector<int> memo = {first * second, first + second};

  while (!nums.empty()) {
    vector<int> new_memo(2 * memo.size());

    const int current = nums.front();
    nums.pop();

    for (const int val : memo) {
      new_memo.push_back(val * current);
      new_memo.push_back(val + current);
    }

    memo = new_memo;
  }

  for (const int result : memo) {
    if (result == target) {
      return true;
    }
  }
  return false;
}

pair<int, queue<int>> parse(const string &line) {
  const vector<string> tokens = split(line, " ");

  string target_str = tokens[0];
  target_str = target_str.substr(0, target_str.size() - 1);

  int target = stoi(target_str);

  const size_t tokens_size = tokens.size() - 1;
  queue<int> nums;
  for (size_t i = 1; i < tokens_size; ++i) {
    nums.push(stoi(tokens[i]));
  }
  return {target, nums};
}

int solve_day7_pt1(const vector<string> &input) {
  int result = 0;
  for (const string &line : input) {
    auto [target, nums] = parse(line);
    if (can_produce(target, nums)) {
      result += target;
    }
  }
  return result;
}
} // namespace Day7
