#include "day8.hpp"
#include "util.hpp"
#include <iostream>

using namespace std;
using namespace Day8;

int main() {
  // const vector<string> input = read_file("../day7_input");
  const vector<string> input = {
    "............",
    "........0...",
    ".....0......",
    ".......0....",
    "....0.......",
    "......A.....",
    "............",
    "............",
    "........A...",
    ".........A..",
    "............",
    "............",
  };
  cout << solve_pt1(input) << endl;
	
  return 0;
}
