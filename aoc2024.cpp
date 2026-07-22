#include "day12.hpp"
#include "util.hpp"
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day12;

int main() {
  const vector<string> input = util::read_file("../day12_input");
  // clang-format off
  // const vector<string> input = {
  //   "\"\"",
  //   "\"abc\"",
  //   "\"aaa\\\"aaa\"",
  //   "\"\\x27\"",
  //  };
  // clang-format on
  // cout << solve_day8_pt1(input) << endl;

  cout << solve_day12_pt1(input[0]) << endl;
}
