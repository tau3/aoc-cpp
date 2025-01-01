#include "day18.cpp"
#include "util.hpp"
#include <iostream>
#include <ostream>

using namespace std;
using namespace Day18;

int main() {
  const vector<string> input = read_file("../day18_input");
  // clang-format off
//   const vector<string> input = {
// "5,4",
// "4,2",
// "4,5",
// "3,0",
// "2,1",
// "6,3",
// "2,4",
// "1,5",
// "0,6",
// "3,3",
// "2,6",
// "5,1",
// "1,2",
// "5,5",
// "2,5",
// "6,5",
// "1,4",
// "0,4",
// "6,4",
// "1,1",
// "6,1",
// "1,0",
// "0,5",
// "1,6",
// "2,0",
//   };
  // clang-format on

  cout << solve_day18_pt2(input, {70, 70}, 1024) << endl;

  return 0;
}
