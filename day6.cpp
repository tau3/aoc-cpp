#include "day6.hpp"
#include "util.hpp"
#include <cassert>
#include <cstddef>
#include <limits>
#include <unordered_set>
#include <vector>

namespace Day6 {

struct IntsHash {
  size_t operator()(const vector<int> &states) const {
    static function<size_t(const int &)> f = [](const int &val) { return val; };
    return util::hash_code(states, f);
  }
};

size_t next_index(const size_t index, const vector<int> &bank) {
  const size_t size = bank.size();
  assert(index < size);

  size_t result = index + 1;
  if (result == size) {
    result = 0;
  }
  return result;
}

vector<int> next(const vector<int> &bank) {
  size_t max_index = 0;
  int max_val = numeric_limits<int>::min();
  for (size_t i = 0; i < bank.size(); i++) {
    const int current = bank[i];
    if (current > max_val) {
      max_val = current;
      max_index = i;
    }
  }

  vector<int> result = bank;
  result[max_index] = 0;
  size_t current = next_index(max_index, bank);
  while (max_val > 0) {
    result[current]++;
    max_val--;
    current = next_index(current, bank);
  }

  return result;
}

pair<int, int> solve(const string &input) {
  const vector<string> tokens = util::split_by_spaces(input);
  vector<int> current;
  for (const string &token : tokens) {
    current.push_back(stoi(token));
  }

  unordered_set<vector<int>, IntsHash> states;
  int pt1 = 0;
  while (states.insert(current).second) {
    pt1++;
    current = next(current);
  }

  const vector<int> target = current;
  current = next(target);
  size_t pt2 = 1;
  while (current != target) {
    current = next(current);
    pt2++;
  }

  return {pt1, pt2};
}

} // namespace Day6
