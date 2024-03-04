#include "day13.hpp"
#include "util.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {
  const vector<string> input = {
    "#.##..##.",
    "..#.##.#.",
    "##......#",
    "##......#",
    "..#.##.#.",
    "..##..##.",
    "#.#.##.#.",
    "",
    "#...##..#",
    "#....#..#",
    "..##..###",
    "#####.##.",
    "#####.##.",
    "..##..###",
    "#....#..#"};
  cout << solve(input) << endl;

  return 0;
}
