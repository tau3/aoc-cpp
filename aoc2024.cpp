#include "day19.cpp"
#include "util.hpp"
#include <iostream>
#include <ostream>

using namespace std;
using namespace Day19;

int main() {
  const vector<string> input = read_file("../day19_input");
  // clang-format off
  // const vector<string> input = {
  //   "r, wr, b, g, bwu, rb, gb, br",
  //   "",
  //   "brwrr",
  //   "bggr",
  //   "gbbr",
  //   "rrbgbr",
  //   "ubwu",
  //   "bwurrg",
  //   "brgr",
  //   "bbrgwb",
  // };
  // clang-format on

  cout << solve_day19_pt1(input) << endl;

  return 0;
}
