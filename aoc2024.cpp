#include "day21.cpp"
#include "util.hpp"
#include <iostream>
#include <ostream>

using namespace std;
using namespace Day21;

int main() {
    // const vector<string> input = read_file("../day21_input");
    // clang-format off
  const vector<string> input = {
"029A",
"980A",
"179A",
"456A",
"379A",
  };
  // // clang-format on

  cout << solve_day21_pt1(input) << endl;

  return 0;
}
