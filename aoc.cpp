#include "day1.hpp"
#include "util.hpp"
#include <cassert>
#include <ostream>
#include <vector>

using namespace Day1;

int main() {
  const std::vector<std::string> input = util::read_file("../day1_input");
  // clang-format off
  // const vector<string> input = {
  // };
  // clang-format on

  assert(!input.empty());
  std::cout << solve_pt2(input[0]) << std::endl;

  return 0;
}
