#include "day11.hpp"
#include "util.hpp"
#include <cassert>
#include <cstddef>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace Day11 {
	
void mrg(unordered_map<long, long> &counts, const long key,
         const long add_value) {
  cout << "mrg " << key << " " << add_value << endl;
  if (const auto &entry = counts.find(key); entry != counts.end()) {
    entry->second += add_value;
  } else {
    counts[key] = add_value;
  }
}

long asd(const vector<int> &input, const int blinks) {
  unordered_map<long, long> counts;
  for (const int num : input) {
    counts[num] = 1;
  }

  for (int i = 0; i < blinks; ++i) {
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

long solve(const string &input, const int blinks) {
  const vector<string> tokens = split(input, " ");
  vector<int> stones;
  for (const string &token : tokens) {
    stones.push_back(stoi(token));
  }

  return asd(stones, blinks);
}

long solve_day11_pt1(const string &input) { return solve(input, 25); }
long solve_day11_pt2(const string &input) { return solve(input, 75); }

} // namespace Day11
