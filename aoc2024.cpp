#include "day25.hpp"
#include "util.hpp"
#include <cassert>
#include <ostream>
#include <vector>

using namespace std;
using namespace Day25;

int main() {
  // const vector<string> input = util::read_file("../day25_input");
  // clang-format off
  const vector<string> input = {
    "cpy a d",
    "cpy 11 c",
    "cpy 231 b",
    "inc d",
    "dec b",
    "jnz b -2",
    "dec c",
    "jnz c -5",
    "cpy d a",
    "jnz 0 0",
    "cpy a b",
    "cpy 0 a",
    "cpy 2 c",
    "jnz b 2",
    "jnz 1 6",
    "dec b",
    "dec c",
    "jnz c -4",
    "inc a",
    "jnz 1 -7",
    "cpy 2 b",
    "jnz c 2",
    "jnz 1 4",
    "dec b",
    "dec c",
    "jnz 1 -4",
    "jnz 0 0",
    "out b",
    "jnz a -19",
    "jnz 1 -21",
  };
  // clang-format on

  assert(!input.empty());
  cout << solve(input) << endl;

  return 0;
}
