#include "day11.hpp"
#include "util.hpp"

using namespace std;
using namespace Day11;

int main() {
  const vector<string> input = util::read_file("../day11_input");
  // clang-format off
 // const vector<string> input = {
 //   "[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}",
 //   "[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}",
 //   "[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}",
 //  };
 //  // clang-format on

  cout << solve_day11_pt2(input) << endl;
}
