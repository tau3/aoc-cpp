#include "day5.hpp"
#include "util.hpp"

using namespace std;
using namespace Day5;

int main() {
  const vector<string> input = read_file("../day5_input");
  // clang-format off
 // const vector<string> input = {
 //   "3-5",
 //   "10-14",
 //   "16-20",
 //   "12-18",
 //   "",
 //   "1",
 //   "5",
 //   "8",
 //   "11",
 //   "17",
 //   "32",
 //  };
  // clang-format on

  cout << solve_day5_pt1(input) << endl;
}
