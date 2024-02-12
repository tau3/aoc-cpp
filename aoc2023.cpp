#include "day9.hpp"
#include "util.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {
  const vector<string> input = {"0 3 6 9 12 15", "1 3 6 10 15 21",
                                "10 13 16 21 30 45"};

  cout << solve(parse(input)) << " expected 114" << endl;

  // const vector<string> input = read_file("../day4_input");
  // cout << solve_day4_pt1(input) << endl;
  return 0;
}
