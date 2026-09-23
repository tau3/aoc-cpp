#include "day16.hpp"
#include "util.hpp"
#include <cassert>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day16;

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

  string input = "10000";
  cout << solve_pt1(input, 20) << endl;

  return 0;
}
