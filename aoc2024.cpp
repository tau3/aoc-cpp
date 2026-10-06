#include "day22.hpp"
#include "util.hpp"
#include <cassert>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day22;

int main() {
  const vector<string> input = util::read_file("../day22_input");
  // clang-format off
  // const vector<string> input = {
  //   "swap position 4 with position 0",
  //   "swap letter d with letter b",
  //   "reverse positions 0 through 4",
  //   "rotate left 1 step",
  //   "move position 1 to position 4",
  //   "move position 3 to position 0",
  //   "rotate based on position of letter b",
  //   "rotate based on position of letter d",
  // };
  // clang-format on

  assert(!input.empty());
  cout << solve(input) << endl;

  return 0;
}
