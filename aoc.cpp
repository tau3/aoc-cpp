#include "day1.hpp"
#include "util.hpp"
#include <cassert>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day1;

int main() {
  const vector<string> input = util::read_file("../day1_input");
  // clang-format off
  // const vector<string> input = {
  // };
  // clang-format on

  assert(!input.empty());
  cout << solve(input[0]) << endl;

  return 0;
}
