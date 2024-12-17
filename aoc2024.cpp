#include "day6.hpp"
#include "util.hpp"
#include <iostream>

using namespace std;
using namespace Day6;

int main() {
  const vector<string> input = read_file("../day6_input");
  // const vector<string> input = {
  //   "....#.....",
  //   ".........#",
  //   "..........",
  //   "..#.......",
  //   ".......#..",
  //   "..........",
  //   ".#..^.....",
  //   "........#.",
  //   "#.........",
  //   "......#...",
  // };
  cout << solve_day6_pt1(input) << endl;

  return 0;
}
