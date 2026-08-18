#include "day24.hpp"
#include "util.hpp"
#include <cassert>
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day24;

int main() {
  const vector<string> input = util::read_file("../day24_input");
  // clang-format off
  // const vector<string> input = {
  //   "1",
  //   "2",
  //   "3",
  //   "4",
  //   "5",
  //   "7",
  //   "8",
  //   "9",
  //   "10",
  //   "11",
  // };
  // clang-format on

  assert(!input.empty());
  cout << solve_day24_pt1(input) << endl;

  return 0;
}
