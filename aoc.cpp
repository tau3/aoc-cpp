#include "day2.hpp"
#include "util.hpp"
#include <cassert>
#include <ostream>
#include <vector>

using namespace Day2;
using namespace std;

int main() {
  const vector<string> input = util::read_file("../day2_input");
  // clang-format off
  // const vector<string> input = {
  //   "5 9 2 8",
  //   "9 4 7 3",
  //   "3 8 6 5",
  // };
  // clang-format on

  assert(!input.empty());
  cout << solve_pt2(input) << endl;

  return 0;
}
