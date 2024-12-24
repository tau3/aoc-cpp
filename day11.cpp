#include "day11.hpp"
#include "util.hpp"
#include <cassert>
#include <cstddef>
#include <ostream>
#include <vector>

namespace Day11 {
bool is_only_zeros(const string &num) {
  for (size_t i = 0; i < num.size(); ++i) {
    if (num[i] != '0') {
      return false;
    }
  }
  return true;
}

vector<int> blink(const vector<int> &stones) {
  vector<int> result;
  const size_t current_size = stones.size();
  const size_t new_size = stones.size() * 2;
  assert(new_size > current_size);
  result.reserve(new_size);

  for (const int num : stones) {
    if (num == 0) {
      result.push_back(1);
    } else {
      const string num_str = to_string(num);
      if (num_str.size() % 2 == 0) {
        const size_t middle = num_str.size() / 2;
        const string left = num_str.substr(0, middle);
        result.push_back(stoi(left));

        const string right = num_str.substr(middle);
        if (is_only_zeros(right)) {
          result.push_back(0);
        } else {
          result.push_back(stoi(right));
        }
      } else {
        result.push_back(num * 2024);
      }
    }
  }
  return result;
}

int solve(const string &input, const int blinks) {
  const vector<string> tokens = split(input, " ");
  vector<int> stones;
  for (const string &token : tokens) {
    stones.push_back(stoi(token));
  }
  for (int i = 0; i < blinks; ++i) {
    cout << "blink=" << i << ", stone=" << stones[0]
         << ", size=" << stones.size() << endl;
    stones = blink(stones);
  }
  return stones.size();
}

int solve_day11_pt1(const string &input) { return solve(input, 25); }
int solve_day11_pt2(const string &input) { return solve(input, 75); }
} // namespace Day11
