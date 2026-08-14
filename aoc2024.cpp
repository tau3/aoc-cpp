#include "day21.hpp"
#include "util.hpp"
#include <iostream>
#include <optional>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day21;

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

  // cout << solve_day20_pt1(29000000) << endl;

  Weapon weapon = Weapon("Shortsword", 10, 5, 0);
  Armor armor = Armor("Platemail", 102, 0, 5);
  Player player = Player(8, weapon, armor, nullopt, nullopt);
  Boss boss = Boss(12, 7, 2);

  cout << fight(&player, &boss) << endl;

  return 0;
}
