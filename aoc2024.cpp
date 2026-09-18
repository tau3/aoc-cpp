#include "day13.hpp"
#include "util.hpp"
#include <cassert>
#include <vector>

using namespace std;
using namespace Day13;

int main() {
  // const vector<string> input = util::read_file("../day12_input");
  // clang-format off
  // const vector<string> input = {
  //   "cpy 41 a",
  //   "inc a",
  //   "inc a",
  //   "dec a",
  //   "jnz a 2",
  //   "dec a",
  // };
  // clang-format on

  // assert(!input.empty());
  // cout << solve_pt2(input) << endl;

  // cout << solve_pt1(10, 7, 4) << endl;
  cout << solve_pt1(1364, 31, 39) << endl;

  return 0;
}
