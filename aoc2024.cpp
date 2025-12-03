#include "day3.hpp"
#include "util.hpp"

using namespace std;
using namespace Day3;

int main() {
  const vector<string> input = read_file("../day3_input");
  // clang-format off
  // const vector<string> input = {
  //   "987654321111111",
  //   "811111111111119",
  //   "234234234234278",
  //   "818181911112111",
  // };
  // // // clang-format on

  cout << solve_day3_pt2(input) << endl;
}
