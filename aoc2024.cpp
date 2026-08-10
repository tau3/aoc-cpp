#include "day17.hpp"
#include "util.hpp"
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day17;

int main() {
  const vector<string> input = util::read_file("../day17_input");
  // clang-format off
  // const vector<string> input = {
  //     "Butterscotch: capacity -1, durability -2, flavor 6, texture 3, calories 8",
  //     "Cinnamon: capacity 2, durability 3, flavor -2, texture -1, calories 3"
  // };
  // clang-format on

  cout << solve_day17_pt1(input) << endl;
}
