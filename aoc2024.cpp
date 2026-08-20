#include "day1.hpp"
#include "util.hpp"
#include <cassert>
#include <vector>

using namespace std;
using namespace Day1;

int main() {
  // const vector<string> input = util::read_file("../day24_input");
  // clang-format off
  // const vector<string> input = {
  //   "1",
  //   "2",
  //   "3",
  //   "4",
  //   "5",
  //   "7",
  //   "8",
  //   "9",
  //   "10",
  //   "11",
  // };
  // clang-format on

  // assert(!input.empty());

  cout << solve_day1_pt1("R5, L5, R5, R3") << endl;

  return 0;
}
