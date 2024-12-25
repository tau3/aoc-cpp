#include "day14.hpp"
#include "util.hpp"
#include <iostream>
#include <ostream>

using namespace std;
using namespace Day14;

int main() {
  const vector<string> input = read_file("../day14_input");
  // clang-format off
  // const vector<string> input = {
  //   "p=0,4 v=3,-3",
  //   "p=6,3 v=-1,-3",
  //   "p=10,3 v=-1,2",
  //   "p=2,0 v=2,-1",
  //   "p=0,0 v=1,3",
  //   "p=3,0 v=-2,-2",
  //   "p=7,6 v=-1,-3",
  //   "p=3,0 v=-1,-2",
  //   "p=9,3 v=2,3",
  //   "p=7,3 v=-1,2",
  //   "p=2,4 v=2,-3",
  //   "p=9,5 v=-3,-3",
  // };
  // clang-format on

  cout << solve_pt2(input, {101, 103}) << endl;

  return 0;
}
