#include "day2.hpp"
#include "util.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {
  const vector<string> input = read_file("../day2_input");
  // const vector<string> input = {
  //   "7 6 4 2 1",
  //   "1 2 7 8 9",
  //   "9 7 6 2 1",
  //   "1 3 2 4 5",
  //   "8 6 4 4 1",
  //   "1 3 6 7 9",
  // };
  cout << solve_day2_pt1(input) << endl;

  return 0;
}
