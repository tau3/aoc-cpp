#include "day7.hpp"
#include "util.hpp"
#include <cassert>
#include <vector>

using namespace std;
using namespace Day7;

int main() {
  const vector<string> input = util::read_file("../day7_input");
  // clang-format off
  // const vector<string> input = {
  //   "abba[mnop]qrst",
  //   "abcd[bddb]xyyx",
  //   "aaaa[qwer]tyui",
  //   "ioxxoj[asdfgh]zxcvbn",
  // };
  // clang-format on

  assert(!input.empty());
  cout << solve_day7_pt1(input) << endl;

  return 0;
}
