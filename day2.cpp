#include "day2.hpp"
#include "util.hpp"
#include <limits>

namespace Day2 {

using namespace std;

int solve(const vector<string> &input) {
  int result = 0;

  for (const string &line : input) {
    const vector<string> tokens = util::split_by_spaces(line);
    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();
    for (const string &token : tokens) {
      const int num = stoi(token);
      if (num < min) {
        min = num;
      }
      if (num > max) {
        max = num;
      }
    }
    const int diff = max - min;
    result += diff;
  }

  return result;
}

} // namespace Day2
