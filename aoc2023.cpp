#include "day3.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // clang-format off
  const vector<string> input = {
    "467..114..",
    "...*......",
    "..35..633.",
    "......#...",
    "617*......",
    ".....+.58.",
    "..592.....",
    "......755.",
    "...$.*....",
    ".664.598.."
  };
  // clang-format on
  int actual = solve_day3_pt1(input);
  cout << "result = " << actual << endl;
}
