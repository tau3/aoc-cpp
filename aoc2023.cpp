#include "day9.hpp"
#include "util.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {
  const vector<string> input = {"0 3 6 9 12 15", "1 3 6 10 15 21",
                                "10 13 16 21 30 45"};
  // const vector<string> input = read_file("../day9_input");

  cout << solve_pt2(parse(input)) << " expected 2" << endl;

  return 0;
}
