#include "day20.hpp"
#include "util.hpp"
#include <cassert>
#include <cstddef>
#include <vector>

namespace Day20 {

using namespace std;

const size_t MAX = 4294967295;

byte leftmost_mask(const size_t i) {
  assert(i < 8);
  return ((byte)1) << (7 - i);
}

pair<size_t, size_t> solve(const vector<string> &input) {
  const size_t array_size = (MAX / 8) + 1;
  byte *state = new byte[array_size]{};

  for (const string &line : input) {
    const vector<string> tokens = util::split(line, "-");
    const size_t from = stol(tokens[0]);
    const size_t to = stol(tokens[1]);

    for (size_t i = from; i <= to; i++) {
      const size_t byte_index = i / 8;
      const size_t shift = i % 8;
      const byte mask = leftmost_mask(shift);
      state[byte_index] |= mask;
    }
  }

  size_t pt1 = 0;
  size_t pt2 = 0;
  for (size_t i = 0; i < MAX; i++) {
    const size_t byte_index = i / 8;
    const size_t shift = i % 8;
    const byte current = state[byte_index];
    const byte mask = leftmost_mask(shift);

    if ((current & mask) == ((byte)0)) {
      pt2++;
      if (pt1 == 0) {
        pt1 = i;
      }
    }
  }

  return {pt1, pt2};
}

} // namespace Day20
