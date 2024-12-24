#include "day13.hpp"
#include "util.hpp"
#include <iostream>

using namespace std;
using namespace Day13;

int main() {
  const vector<string> input = read_file("../day13_input");
  // const vector<string> input = {
  //   "Button A: X+94, Y+34",
  //   "Button B: X+22, Y+67",
  //   "Prize: X=8400, Y=5400",
  //   "",
  //   "Button A: X+26, Y+66",
  //   "Button B: X+67, Y+21",
  //   "Prize: X=12748, Y=12176",
  //   "",
  //   "Button A: X+17, Y+86",
  //   "Button B: X+84, Y+37",
  //   "Prize: X=7870, Y=6450",
  //   "",
  //   "Button A: X+69, Y+23",
  //   "Button B: X+27, Y+71",
  //   "Prize: X=18641, Y=10279",
  // };
  cout << solve_day13_pt1(input) << endl;

  // cout << "solve: "<< solve_arcade({94,34}, {22,67}, {8400,5400}) << endl;
  // cout << "solve: " << solve_arcade({26, 66}, {67, 21}, {12748, 12176}) << endl;
  // cout << "solve: " << solve_arcade({17, 86}, {84, 37}, {7870, 6450}) <<
  // endl;

  return 0;
}
