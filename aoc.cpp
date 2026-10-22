#include "day5.hpp"
#include "util.hpp"
#include <cassert>
#include <ostream>
#include <vector>

using namespace Day5;
using namespace std;

int main() {
  // const vector<string> input = util::read_file("../day5_input");
  // clang-format off
  const vector<string> input = {
    "0",
    "3",
    "0",
    "1",
    "-3",
  };
  // clang-format on

  assert(!input.empty());
  cout << solve_pt2(input) << endl;

  return 0;
}
