#include "day25.cpp"
#include "util.hpp"
#include <iostream>
#include <ostream>

using namespace std;
using namespace Day25;

int main() {
  const vector<string> input = read_file("../day25_input");
  // clang-format off
  // const vector<string> input = {
  //   "#####",
  //   ".####",
  //   ".####",
  //   ".####",
  //   ".#.#.",
  //   ".#...",
  //   ".....",
  //   "",
  //   "#####",
  //   "##.##",
  //   ".#.##",
  //   "...##",
  //   "...#.",
  //   "...#.",
  //   ".....",
  //   "",
  //   ".....",
  //   "#....",
  //   "#....",
  //   "#...#",
  //   "#.#.#",
  //   "#.###",
  //   "#####",
  //   "",
  //   ".....",
  //   ".....",
  //   "#.#..",
  //   "###..",
  //   "###.#",
  //   "###.#",
  //   "#####",
  //   "",
  //   ".....",
  //   ".....",
  //   ".....",
  //   "#....",
  //   "#.#..",
  //   "#.#.#",
  //   "#####",
  // };
  // clang-format on

  cout << solve_day25_pt1(input) << endl;

  // cout << is_fit({0, 5, 3, 4, 3}, {3, 0, 2, 0, 1}) << endl;

  return 0;
}
