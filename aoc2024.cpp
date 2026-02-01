#include "day8.hpp"
#include "util.hpp"
#include <vector>

using namespace std;
using namespace Day8;

int main() {
  const vector<string> input = util::read_file("../day8_input");
  // clang-format off
 // const vector<string> input = {
 //   "\"\"",
 //   "\"abc\"",
 //   "\"aaa\\\"aaa\"",
 //   "\"\\x27\"",
 //  };
  // clang-format on
 cout << solve_day8_pt1(input) << endl;
}
