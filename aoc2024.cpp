#include "day17.cpp"
#include "util.hpp"
#include <iostream>
#include <ostream>

using namespace std;
using namespace Day17;

int main() {
  const vector<string> input = read_file("../day17_input");
  // clang-format off
//   const vector<string> input = {
// "Register A: 2024",
// "Register B: 0",
// "Register C: 0",
// "",
// "Program: 0,3,5,4,3,0",
//   };
  // clang-format on

 cout << solve_day17_pt2(input) << endl;

  return 0;
}
