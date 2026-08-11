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
  //   "H => HO",
  //   "H => OH",
  //   "O => HH",
  //   "",
  //   "HOH",
  // };
  // // clang-format on

  cout << solve_day_19_pt1(input) << endl;
}
