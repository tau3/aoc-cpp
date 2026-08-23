#include "day2.hpp"
#include "util.hpp"
#include <cassert>
#include <vector>

using namespace std;
using namespace Day2;

int main() {
  const vector<string> input = util::read_file("../day2_input");
  // clang-format off
  // const vector<string> input = {
  //   "ULL",
  //   "RRDDD",
  //   "LURDL",
  //   "UUUUD",
  // };
  // clang-format on

  assert(!input.empty());
  cout << solve_day2_pt1(input) << endl;

  return 0;
}
