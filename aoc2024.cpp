#include "day4.hpp"
#include "util.hpp"

using namespace std;
using namespace Day4;

int main() {
  // const vector<string> input = read_file("../day3_input");
  // clang-format off
  const vector<string> input = {
"..@@.@@@@.",
"@@@.@.@.@@",
"@@@@@.@.@@",
"@.@@@@..@.",
"@@.@@@@.@@",
".@@@@@@@.@",
".@.@.@.@@@",
"@.@@@.@@@@",
".@@@@@@@@.",
"@.@.@@@.@.",
  };
  // // // clang-format on

  cout << solve_day4_pt1(input) << endl;
}
