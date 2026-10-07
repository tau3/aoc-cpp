#include "day23.hpp"
#include "util.hpp"
#include <cassert>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day23;

int main() {
  // const vector<string> input = util::read_file("../day22_input");
  // clang-format off
  const vector<string> input = {
    "cpy 2 a",
    "tgl a",
    "tgl a",
    "tgl a",
    "cpy 1 a",
    "dec a",
    "dec a",
  };
  // clang-format on

  assert(!input.empty());
  cout << solve(input) << endl;

  return 0;
}
