#include "day4.hpp"
#include "util.hpp"
#include <functional>
#include <unordered_set>

namespace Day4 {

bool is_valid(const string &passphrase) {
  const vector<string> tokens = util::split(passphrase, " ");

  unordered_set<string> distinct;
  for (const string &token : tokens) {
    if (!distinct.insert(token).second) {
      return false;
    }
  }
  return true;
}

bool is_valid_pt2(const string &passphrase) {
  vector<string> tokens = util::split(passphrase, " ");

  unordered_set<string> distinct;
  for (string &token : tokens) {
    sort(token.begin(), token.end());
    if (!distinct.insert(token).second) {
      return false;
    }
  }
  return true;
}

size_t solve(const vector<string> &input,
             const function<bool(const string &)> &predicate) {
  size_t result = 0;
  for (const string &line : input) {
    result += predicate(line);
  }
  return result;
}

size_t solve_pt1(const vector<string> &input) { return solve(input, is_valid); }

size_t solve_pt2(const vector<string> &input) {
  return solve(input, is_valid_pt2);
}

} // namespace Day4
