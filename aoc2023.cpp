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
  // const vector<string> input = read_file("../day10_input");

  const vector<string> input = {
    "...........",
    ".S-------7.",
    ".|F-----7|.",
    ".||.....||.",
    ".||.....||.",
    ".|L-7.F-J|.",
    ".|..|.|..|.",
    ".L--J.L--J.",
    "..........."
  };
  
  cout << solve_pt1(input) << " expected 4" << endl;

  return 0;
}
