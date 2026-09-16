#include "day11.hpp"
#include "util.hpp"
#include <cassert>
#include <vector>

using namespace std;
using namespace Day11;

int main() {
  // const vector<string> input = util::read_file("../day10_input");
  // clang-format off
  // const vector<string> input = {
  //   "value 5 goes to bot 2",
  //   "bot 2 gives low to bot 1 and high to bot 0",
  //   "value 3 goes to bot 1",
  //   "bot 1 gives low to output 1 and high to bot 0",
  //   "bot 0 gives low to output 2 and high to output 0",
  //   "value 2 goes to bot 2",
  // };
  // clang-format on

  // assert(!input.empty());
  // cout << solve_day10(input) << endl;

  cout << solve_pt1_example() << endl;
  
  return 0;
}
