#include "day10.hpp"
#include "util.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {
  const vector<string> input = {
    ".....",
    ".S-7.",
    ".|.|.",
    ".L-J.",
    "....."
  };
  // const vector<string> input = read_file("../day9_input");

  cout << solve_pt1(input) << " expected 4" << endl;

  return 0;
}
