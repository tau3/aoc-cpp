#include "day1.hpp"
#include "util.hpp"

using namespace std;
using namespace Day1;

int main() {
  // const vector<string> input = read_file("../day16_input");
  // clang-format off
  const vector<string> input = {
    "L68",
    "L30",
    "R48",
    "L5",
    "R60",
    "L55",
    "L1",
    "L99",
    "R14",
    "L82",
};
  // clang-format on

  cout << solve_day1_pt1(input) << endl;

  return 0;
}
