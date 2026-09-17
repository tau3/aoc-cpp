#include "day12.hpp"
#include "util.hpp"
#include <cassert>
#include <vector>

using namespace std;
using namespace Day12;

int main() {
  // const vector<string> input = util::read_file("../day10_input");
  // clang-format off
  const vector<string> input = {
    "cpy 41 a",
    "inc a",
    "inc a",
    "dec a",
    "jnz a 2",
    "dec a",
  };
  // clang-format on

  assert(!input.empty());
  cout << solve_pt1(input) << endl;

  return 0;
}
