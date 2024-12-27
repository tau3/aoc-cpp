#include "day16.hpp"
#include "util.hpp"

using namespace std;
using namespace Day16;

int main() {
  // const vector<string> input = read_file("../day16_input");
  // clang-format off
  const vector<string> input = {
"###############",
"#.......#....E#",
"#.#.###.#.###.#",
"#.....#.#...#.#",
"#.###.#####.#.#",
"#.#.#.......#.#",
"#.#.#####.###.#",
"#...........#.#",
"###.#.#####.#.#",
"#...#.....#.#.#",
"#.#.#.###.#.#.#",
"#.....#...#.#.#",
"#.###.#.#.#.#.#",
"#S..#.....#...#",
"############### ",
};
  // clang-format on

  cout << solve_day16_pt1(input) << endl;

  return 0;
}
