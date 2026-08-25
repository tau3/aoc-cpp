#include "day3.hpp"
#include "util.hpp"
#include <cassert>
#include <vector>

using namespace std;
using namespace Day3;

int main() {
  const vector<string> input = util::read_file("../day3_input");
  // clang-format off
  // const vector<string> input = {
  //   "ULL",
  //   "RRDDD",
  //   "LURDL",
  //   "UUUUD",
  // };
  // // clang-format on

  assert(!input.empty());
  cout << solve_day3_pt2(input) << endl;

  return 0;
}
