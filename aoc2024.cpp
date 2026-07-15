#include "day10.hpp"
#include "util.hpp"
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day10;

int main() {
  // const vector<string> input = util::read_file("../day8_input");
  // clang-format off
  // const vector<string> input = {
  //   "\"\"",
  //   "\"abc\"",
  //   "\"aaa\\\"aaa\"",
  //   "\"\\x27\"",
  //  };
  // clang-format on
  // cout << solve_day8_pt1(input) << endl;

  cout << look_and_say_step("1211") << endl;
}
