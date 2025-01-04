#include "util.hpp"
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

namespace Day19 {

bool can_be_made(const string &design, const vector<string> &patterns) {
  if (design.empty()) {
    return true;
  }

  for (const string &prefix : patterns) {
    if (starts_with(design, prefix)) {
      const string suffix = design.substr(prefix.size());
      if (can_be_made(suffix, patterns)) {
        return true;
      }
    }
  }

  return false;
}

long count_ways_to_build(const string &design, const vector<string> &patterns,
                        unordered_map<string, long> &cache) {
  if (design.empty()) {
    return 1;
  }

  if (const auto &entry = cache.find(design); entry != cache.end()) {
    return entry->second;
  }

  long result = 0;
  for (const string &prefix : patterns) {
    if (starts_with(design, prefix)) {
      const string suffix = design.substr(prefix.size());
      result += count_ways_to_build(suffix, patterns, cache);
    }
  }

  cache[design] = result;
  return result;
}

int solve_day19_pt1(const vector<string> &input) {
  const string all_patterns = input[0];
  const vector<string> patterns = split(all_patterns, ", ");
  const vector<string> designs = vector<string>(input.begin() + 2, input.end());

  int result = 0;
  for (const string &design : designs) {
    if (can_be_made(design, patterns)) {
      ++result;
    }
  }

  return result;
}

long solve_day19_pt2(const vector<string> &input) {
  const string all_patterns = input[0];
  const vector<string> patterns = split(all_patterns, ", ");
  const vector<string> designs = vector<string>(input.begin() + 2, input.end());

  long result = 0;
  unordered_map<string, long> cache;
  for (const string &design : designs) {
    result += count_ways_to_build(design, patterns, cache);
  }

  return result;
}

} // namespace Day19
