#include "day22.cpp"
#include "util.hpp"
#include <iostream>
#include <ostream>

using namespace std;
using namespace Day22;

int main() {
  const vector<string> input = read_file("../day22_input");
  // clang-format off
  // const vector<string> input = {
  //   "1",
  //   "10",
  //   "100",
  //   "2024",
  // };
  // clang-format on

  cout << solve_day22_pt1(input) << endl;

  return 0;
}
