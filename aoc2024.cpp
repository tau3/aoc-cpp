#include "day18.hpp"
#include "util.hpp"
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day18;

int main() {
  const vector<string> input = util::read_file("../day18_input");
  // clang-format off
  // const vector<string> input = {
  //   ".#.#.#",
  //   "...##.",
  //   "#....#",
  //   "..#...",
  //   "#.#..#",
  //   "####.."
  // };
  // // clang-format on

  // cout << solve_day18_pt1(input) << endl;
  cout << solve(input, 100) << endl;
}
