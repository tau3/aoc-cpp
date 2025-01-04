#include "day20.cpp"
#include "util.hpp"
#include <iostream>
#include <ostream>

using namespace std;
using namespace Day20;

int main() {
    // const vector<string> input = read_file("../day19_input");
    // clang-format off
  const vector<string> input = {
"###############",
"#...#...#.....#",
"#.#.#.#.#.###.#",
"#S#...#.#.#...#",
"#######.#.#.###",
"#######.#.#...#",
"#######.#.###.#",
"###..E#...#...#",
"###.#######.###",
"#...###...#...#",
"#.#####.#.###.#",
"#.#...#.#.#...#",
"#.#.#.#.#.#.###",
"#...#...#...###",
"###############",
  };
  // // clang-format on

  cout << solve_day20_pt1(input) << endl;

  return 0;
}
