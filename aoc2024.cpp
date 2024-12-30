#include "day17.cpp"
#include "util.hpp"
#include <iostream>
#include <ostream>

using namespace std;
using namespace Day17;

int main() {
  // const vector<string> input = read_file("../day15_input");
  // clang-format off
  const vector<string> input = {
"Register A: 729",
"Register B: 0",
"Register C: 0",
"",
"Program: 0,1,5,4,3,0",
  };
  // clang-format on

  cout << solve_day17_pt1(input) << endl;

  return 0;
}
