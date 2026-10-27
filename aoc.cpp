#include "day7.hpp"
#include "util.hpp"
#include <cassert>
#include <ostream>
#include <vector>

using namespace Day7;
using namespace std;

int main() {
  const vector<string> input = util::read_file("../day7_input");
  // clang-format off
  // const vector<string> input = {
  // "pbga (66)",
  // "xhth (57)",
  // "ebii (61)",
  // "havc (66)",
  // "ktlj (57)",
  // "fwft (72) -> ktlj, cntj, xhth",
  // "qoyq (66)",
  // "padx (45) -> pbga, havc, qoyq",
  // "tknk (41) -> ugml, padx, fwft",
  // "jptl (61)",
  // "ugml (68) -> gyxo, ebii, jptl",
  // "gyxo (61)",
  // "cntj (57)",
  // };
  // clang-format on

  assert(!input.empty());
  cout << solve_pt2(input, "eqgvf") << endl;

  return 0;
}
