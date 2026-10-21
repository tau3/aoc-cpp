#include "day4.hpp"
#include "util.hpp"
#include <cassert>
#include <ostream>
#include <vector>

using namespace Day4;
using namespace std;

int main() {
  const vector<string> input = util::read_file("../day4_input");
  // clang-format off
  // const vector<string> input = {
  //   "aa bb cc dd ee",
  //   "aa bb cc dd aa",
  //   "aa bb cc dd aaa",
  // };
  // clang-format on

  assert(!input.empty());
  cout << solve(input) << endl;

  return 0;
}
