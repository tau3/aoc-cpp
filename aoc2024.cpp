#include "day11.hpp"
#include "util.hpp"
#include <iostream>

using namespace std;
using namespace Day11;

int main() {
  const vector<string> input = read_file("../day11_input");
  // const vector<string> input = { "125 17" };
  cout << solve_day11_pt1(input[0]) << endl;

  return 0;
}
