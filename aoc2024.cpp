#include "day7.hpp"
#include "util.hpp"

using namespace std;
using namespace Day7;

int main() {
  vector<string> input = util::read_file("../day7_input");
  // clang-format off
//  const vector<string> input = {
// ".......S.......",
// "...............",
// ".......^.......",
// "...............",
// "......^.^......",
// "...............",
// ".....^.^.^.....",
// "...............",
// "....^.^...^....",
// "...............",
// "...^.^...^.^...",
// "...............",
// "..^...^.....^..",
// "...............",
// ".^.^.^.^.^...^.",
// "...............",
//   };
  // clang-format on

  cout << solve_day7_pt2(input) << endl;
}
