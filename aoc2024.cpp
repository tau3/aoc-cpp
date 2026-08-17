#include "day22.hpp"
#include "util.hpp"
#include <deque>
#include <iostream>
#include <optional>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day22;

int main() {
  // const vector<string> input = util::read_file("../day19_input");
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

  // cout << solve_day19_pt2(input) << endl;

  deque<State> states;
  State state = {
      {50, 500},
      {58, 9},
      true,
      0,
      {{Effect::POISON, 0}, {Effect::RECHARGE, 0}, {Effect::SHIELD, 0}}};
  states.push_back(state);

  cout << solve(states) << endl;

  return 0;
}
