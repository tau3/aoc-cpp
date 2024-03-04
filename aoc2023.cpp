#include "day13.hpp"
#include "util.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {
  // const vector<string> input = {
  //   "#.##..##.",
  //   "..#.##.#.",
  //   "##......#",
  //   "##......#",
  //   "..#.##.#.",
  //   "..##..##.",
  //   "#.#.##.#.",
  //   "",
  //   "#...##..#",
  //   "#....#..#",
  //   "..##..###",
  //   "#####.##.",
  //   "#####.##.",
  //   "..##..###",
  //   "#....#..#"};
  const vector<string> input = read_file("../day13_input");
  cout << solve_day13_pt1(input) << endl;

  return 0;
}
