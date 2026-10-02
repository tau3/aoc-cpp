#include "day20.hpp"
#include "util.hpp"
#include <cassert>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day20;

int main() {
  const vector<string> input = util::read_file("../day20_input");
  // clang-format off
  // const vector<string> input = {
    // "5-8",
    // "0-2",
    // "4-7",
  // };
  // clang-format on

  assert(!input.empty());
  cout << solve(input).second << endl;

  return 0;
}
