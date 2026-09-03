#include "day9.hpp"
#include "util.hpp"
#include <cassert>
#include <vector>

using namespace std;
using namespace Day9;

void check_decompress(const string &input, const string &expected) {
  const string actual = decompress(input);
  cout << input << " -> act=" << actual << ", exp=" << expected << " "
  << ((actual == expected) ? "true" : "false") << endl;
}

int main() {
  // const vector<string> input = util::read_file("../day8_input");
  // clang-format off
  // const vector<string> input = {
  //   "rect 3x2",
  //   "rotate column x=1 by 1",
  //   "rotate row y=0 by 4",
  //   "rotate column x=1 by 1",
  // };
  // clang-format on

  // assert(!input.empty());
  // cout << solve_day8_pt1(input) << endl;

  // check_decompress("ADVENT", "ADVENT");
  // check_decompress("A(1x5)BC", "ABBBBBC");
  // check_decompress("(3x3)XYZ", "XYZXYZXYZ");
  // check_decompress("A(2x2)BCD(2x2)EFG", "ABCBCDEFEFG");
  check_decompress("(6x1)(1x3)A", "(1x3)A");
  // check_decompress("X(8x2)(3x3)ABCY", "X(3x3)ABC(3x3)ABCY");

  return 0;
}
