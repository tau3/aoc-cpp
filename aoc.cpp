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
  //   "abcde fghij",
  //   "abcde xyz ecdab",
  //   "a ab abc abd abf abj",
  //   "iiii oiii ooii oooi oooo",
  //   "oiii ioii iioi iiio",
  // };
  // clang-format on

  assert(!input.empty());
  cout << solve_pt2(input) << endl;

  return 0;
}
