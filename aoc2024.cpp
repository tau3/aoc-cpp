#include "day3.hpp"
#include "util.hpp"
#include <iostream>

using namespace std;

int main() {
  // const vector<string> input = read_file("../day2_input");
  // const vector<string> input = {
  //   "7 6 4 2 1",
  //   "1 2 7 8 9",
  //   "9 7 6 2 1",
  //   "1 3 2 4 5",
  //   "8 6 4 4 1",
  //   "1 3 6 7 9",
  // };
  // const string input =
      // "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";
  const string input = read_file("../day3_input")[0];
  cout << solve(input) << endl;

  return 0;
}
