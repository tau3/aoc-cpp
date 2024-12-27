#include "day12.hpp"
#include "util.hpp"

using namespace std;
using namespace Day12;

int main() {
  // const vector<string> input = read_file("../day12_input");
  // clang-format off
  const vector<string> input = {
"RRRRIICCFF",
"RRRRIICCCF",
"VVRRRCCFFF",
"VVRCCCJFFF",
"VVVVCJJCFE",
"VVIVCCJJEE",
"VVIIICJJEE",
"MIIIIIJJEE",
"MIIISIJEEE",
"MMMISSJEEE",
};
  // clang-format on

  cout << solve_day12_pt1(input) << endl;

  return 0;
}
