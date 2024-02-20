#include "day10.hpp"
#include "util.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {
//   const vector<string> input = {
//     ".....",
//     ".S-7.",
//     ".|.|.",
//     ".L-J.",
//     "....."
//   };
  // const vector<string> input = {
    // "..F7.",
    // ".FJ|.",
    // "SJ.L7",
    // "|F--J",
    // "LJ..."
  // };
  const vector<string> input = read_file("../day10_input");

  cout << solve_pt1(input) << " expected 8" << endl;

  return 0;
}
