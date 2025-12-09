#include "day9.hpp"
#include "util.hpp"

using namespace std;
using namespace Day9;

int main() {
  const vector<string> input = util::read_file("../day9_input");
  // clang-format off
 // const vector<string> input = {
 //   "7,1",
 //   "11,1",
 //   "11,7",
 //   "9,7",
 //   "9,5",
 //   "2,5",
 //   "2,3",
 //   "7,3",
 //  };
  // clang-format on

  cout << solve_day9_pt1(input) << endl;
}
