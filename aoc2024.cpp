#include "day6.hpp"
#include "util.hpp"

using namespace std;
using namespace Day6;

int main() {
  const vector<string> input = util::read_file("../day6_input");
  // clang-format off
 // const vector<string> input = {
 //   "123 328  51 64 ",
 //   " 45 64  387 23 ",
 //   "  6 98  215 314",
 //   "*   +   *   +  ",
 //  };
  // clang-format on

  cout << solve_day6_pt1(input) << endl;
}
