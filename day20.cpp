#include "day20.hpp"
#include "util.hpp"
#include <stdexcept>
#include <vector>

namespace Day20 {

using namespace std;

const size_t MAX = 4294967295;

size_t solve(const vector<string> &input) {
  vector<bool> state(MAX, true);

  for (const string &line : input) {
    const vector<string> tokens = util::split(line, "-");
    const size_t from = stol(tokens[0]);
    const size_t to = stol(tokens[1]);

    for (size_t i = from; i <= to; i++) {
      state[i] = false;
    }
  }

  for (size_t i = 0; i < MAX; i++) {
    if (state[i]) {
      return i;
    }
  }

  throw runtime_error("unreachable");
}

} // namespace Day20
