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
  //   "5 1 9 5",
  //   "7 5 3",
  //   "2 4 6 8",
  // };
  // clang-format on

  assert(!input.empty());
  cout << solve(input) << endl;

  return 0;
}
