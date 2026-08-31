#include "day6.hpp"
#include "util.hpp"
#include <cassert>
#include <vector>

using namespace std;
using namespace Day6;

int main() {
  const vector<string> input = util::read_file("../day6_input");
  // clang-format off
  // const vector<string> input = {
  //   "eedadn",
  //   "drvtee",
  //   "eandsr",
  //   "raavrd",
  //   "atevrs",
  //   "tsrnev",
  //   "sdttsa",
  //   "rasrtv",
  //   "nssdts",
  //   "ntnada",
  //   "svetve",
  //   "tesnvt",
  //   "vntsnd",
  //   "vrdear",
  //   "dvrsen",
  //   "enarar",
  // };
  // clang-format on

  assert(!input.empty());
  cout << solve_day6(input) << endl;

  return 0;
}
