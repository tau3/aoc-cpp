#include "day17.hpp"
#include <cstddef>

namespace Day17 {

int how_many_ways(const vector<int> &containers,
                  const unordered_map<int, int> &cache, const int limit) {
  int result = 0;
  for (size_t i = 0; i < containers.size(); i++) {
    const int current = containers[i];
    if (current > limit) {
      continue;
    }

    if (current == limit) {
      result++;
      continue;
    }

    vector<int> remaining = containers;
    remaining.erase(remaining.begin() + i);

    const int current_limit = limit - current;
    result += how_many_ways(remaining, cache, current_limit);
  }

  return result;
}

} // namespace Day17
