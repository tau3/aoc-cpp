#include "day9.hpp"
#include "util.hpp"
#include <iostream>

using namespace std;
using namespace Day9;

int main() {
  // const vector<string> input = read_file("../day9_input");
  const vector<string> input = {"2333133121414131402"};
  cout << solve_day9_pt2(input[0]) << endl;

  return 0;
}
