#include "day4.hpp"
#include "util.hpp"
#include <iostream>

using namespace std;

int main() {
  // const vector<string> input = read_file("../day4_input");
  const vector<string> input = {
    "MMMSXXMASM",
    "MSAMXMSMSA",
    "AMXSXMAAMM",
    "MSAMASMSMX",
    "XMASAMXAMM",
    "XXAMMXXAMA",
    "SMSMSASXSS",
    "SAXAMASAAA",
    "MAMMMXMMMM",
    "MXMXAXMASX",
  };
  cout << solve_day4_pt2(input) << endl;

  return 0;
}
