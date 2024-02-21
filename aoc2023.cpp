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

  // const vector<string> input = {
  //   "...........",
  //   ".S-------7.",
  //   ".|F-----7|.",
  //   ".||.....||.",
  //   ".||.....||.",
  //   ".|L-7.F-J|.",
  //   ".|..|.|..|.",
  //   ".L--J.L--J.",
  //   "..........."
  // };

  // const vector<string> input = {
  //   ".F----7F7F7F7F-7....",
  //   ".|F--7||||||||FJ....",
  //   ".||.FJ||||||||L7....",
  //   "FJL7L7LJLJ||LJ.L-7..",
  //   "L--J.L7...LJS7F-7L7.",
  //   "....F-J..F7FJ|L7L7L7",
  //   "....L7.F7||L7|.L7L7|",
  //   ".....|FJLJ|FJ|F7|.LJ",
  //   "....FJL-7.||.||||...",
  //   "....L---J.LJ.LJLJ..."
  // };
  
  cout << solve_pt2(input) << " expected 4" << endl;

  return 0;
}
