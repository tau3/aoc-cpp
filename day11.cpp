#include "day11.hpp"
#include "util.hpp"
#include <cassert>
#include <cstddef>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace Day11 {

using num_t = unsigned long;

vector<num_t> blink(const vector<num_t> &stones) {
  vector<num_t> result;
  const size_t current_size = stones.size();
  const size_t new_size = stones.size() * 2;
  assert(new_size > current_size);
  result.reserve(new_size);

  for (const num_t num : stones) {
    if (num == 0) {
      result.push_back(1);
    } else {
      const string num_str = to_string(num);
      const size_t size = num_str.size();
      if (size % 2 == 0) {
        const size_t middle = size / 2;
        string left, right;
        for (size_t i = 0; i < size; ++i) {
          if (i < middle) {
            left += num_str[i];
          } else {
            right += num_str[i];
          }
        }
        // cout << "left=" << left << ", right= " << right << ", num=" <<
        // num_str
        // << endl;
        result.push_back(stoi(left));
        // cout << "right=" << right << endl;
        result.push_back(stoi(right));
      } else {
        const num_t val = num * 2024;
        assert(val > num);
        result.push_back(val);
      }
    }
  }
  return result;
}

int solve(const string &input, const int blinks) {
  const vector<string> tokens = split(input, " ");
  vector<num_t> stones;
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

int solve_day11_pt2(const string &input) { return solve(input, 75); }

void mrg(unordered_map<long, long>& counts, const long key,
         const long add_value) {
  cout << "mrg " << key << " " << add_value << endl;
  if (const auto &entry = counts.find(key); entry != counts.end()) {
    entry->second += add_value;
  } else {
    counts[key] = add_value;
  }
}

long asd(const vector<int> &input) {
  unordered_map<long, long> counts;
  for (const int num : input) {
    counts[num] = 1;
  }

  for (int i = 0; i < 25; ++i) {
    unordered_map<long, long> current;
    for (const auto &e : counts) {
      const long num = e.first;
      const long count = e.second;
      if (num == 0) {
        mrg(current, 1, count);
      } else {
        const string num_str = to_string(num);
        const size_t size = num_str.size();
        if (size % 2 == 0) {
          const size_t middle = size / 2;
          string left, right;
          for (size_t i = 0; i < size; ++i) {
            if (i < middle) {
              left += num_str[i];
            } else {
              right += num_str[i];
            }
          }

          mrg(current, stoi(left), count);
          mrg(current, stoi(right), count);
        } else {
          const long val = num * 2024;
          mrg(current, val, count);
        }
      }
    }
    counts = current;
  }

  long result = 0;
  for (const auto &entry : counts) {
    result += entry.second;
  }
  return result;
}

long solve_day11_pt1(const string &input) {
  const vector<string> tokens = split(input, " ");
  vector<int> stones;
  for (const string &token : tokens) {
    stones.push_back(stoi(token));
  }

  return asd(stones);
}

} // namespace Day11
