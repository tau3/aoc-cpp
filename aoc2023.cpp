#include "day14.hpp"
#include "util.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {
  // vector<string> input = {
  //   "O....#....",
  //   "O.OO#....#",
  //   ".....##...",
  //   "OO.#O....O",
  //   ".O.....O#.",
  //   "O.#..O.#.#",
  //   "..O..#O..O",
  //   ".......O..",
  //   "#....###..",
  //   "#OO..#...."
  // };
  vector<string> input = read_file("../day14_input");
  cout << solve_day14_pt1(input) << endl;

  return 0;
}
