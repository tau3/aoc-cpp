#include "day4.hpp"
#include "util.hpp"
#include <cassert>
#include <vector>

using namespace std;
using namespace Day4;

int main() {
  // const vector<string> input = util::read_file("../day4_input");
  // clang-format off
  const vector<string> input = {
    "aaaaa-bbb-z-y-x-123[abxyz]",
    "a-b-c-d-e-f-g-h-987[abcde]",
    "not-a-real-room-404[oarel]",
    "totally-real-room-200[decoy]",
  };
  // clang-format on

  assert(!input.empty());
  cout << solve_day4_pt2(input) << endl;

  return 0;
}
