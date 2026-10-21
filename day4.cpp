#include "day4.hpp"
#include "util.hpp"
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

size_t solve(const vector<string> &input) {
  size_t result = 0;
  for (const string &line : input) {
    result += is_valid(line);
  }
  return result;
}

} // namespace Day4
