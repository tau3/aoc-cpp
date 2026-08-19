#include "day25.hpp"
#include "util.hpp"
#include <cassert>
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day25;

int main() {
  // const vector<string> input = util::read_file("../day24_input");
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

  // assert(!input.empty());
  cout << solve_day25_pt1(2947, 3029) << endl;

  // cout << iterate(1, 6, 1, [](const auto x) -> auto { return x + 1; }) <<
  // endl;
  return 0;
}
