#include "day7.hpp"
#include "util.hpp"
#include <iostream>

using namespace std;
using namespace Day7;

int main() {
  const vector<string> input = read_file("../day7_input");
  // const vector<string> input = {
  //   "190: 10 19",
  //   "3267: 81 40 27",
  //   "83: 17 5",
  //   "156: 15 6",
  //   "7290: 6 8 6 15",
  //   "161011: 16 10 13",
  //   "192: 17 8 14",
  //   "21037: 9 7 18 13",
  //   "292: 11 6 16 20",
  // };
  cout << solve_day7_pt2(input) << endl;
	
  return 0;
}
