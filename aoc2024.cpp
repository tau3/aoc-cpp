#include "day14.hpp"
#include "util.hpp"
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day14;

int main() {
  const vector<string> input = util::read_file("../day14_input");
  // clang-format off
  // const vector<string> input = {
  // "Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds.",
  // "Dancer can fly 16 km/s for 11 seconds, but then must rest for 162 seconds."
  // };
  // clang-format on

  cout << solve_day14_pt1(input) << endl;
}
