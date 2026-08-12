#include "day19.hpp"
#include "util.hpp"
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day19;

int main() {
  const vector<string> input = util::read_file("../day19_input");
  // clang-format off
  // const vector<string> input = {
  //   "e => H",
  //   "e => O",
  //   "H => HO",
  //   "H => OH",
  //   "O => HH",
  //   "",
  //   "HOH",
  // };
  // clang-format on

  cout << solve_day19_pt2(input) << endl;
}
