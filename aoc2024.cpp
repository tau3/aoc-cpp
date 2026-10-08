#include "day24.hpp"
#include "util.hpp"
#include <cassert>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day24;

int main() {
  const vector<string> input = util::read_file("../day24_input");
  // clang-format off
  // const vector<string> input = {
  //     "###########",
  //     "#0.1.....2#",
  //     "#.#######.#",
  //     "#4.......3#",
  //     "###########",
  // };
  // clang-format on

  assert(!input.empty());
  cout << solve(input) << endl;

  return 0;
}
