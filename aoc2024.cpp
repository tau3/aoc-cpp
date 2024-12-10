#include "day1.hpp"
#include "util.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {
  const vector<string> input = read_file("../day1_input");
  // const vector<string> input = {
  //   "3   4",
  //   "4   3",
  //   "2   5",
  //   "1   3",
  //   "3   9",
  //   "3   3"
  // };
  cout << solve_day1_pt2(input) << endl;

  return 0;
}
