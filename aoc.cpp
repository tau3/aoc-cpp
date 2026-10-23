#include "day6.hpp"
#include "util.hpp"
#include <cassert>
#include <ostream>
#include <vector>

using namespace Day6;
using namespace std;

int main() {
  // const vector<string> input = util::read_file("../day5_input");
  // clang-format off
  // const vector<string> input = {
  //   "0",
  //   "3",
  //   "0",
  //   "1",
  //   "-3",
  // };
  // clang-format on

  // assert(!input.empty());
  // cout << solve_pt2(input) << endl;

  cout
      << solve(
             "2	8	8	5	4	2	3	1	"
             "5	5	1	2	15	13	5	14")
      << endl;

  return 0;
}
