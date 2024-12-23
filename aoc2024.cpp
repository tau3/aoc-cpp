#include "day10.hpp"
#include "util.hpp"
#include <iostream>

using namespace std;
using namespace Day10;

int main() {
  const vector<string> input = read_file("../day10_input");
  // const vector<string> input = {
  //   "89010123",
  //   "78121874",
  //   "87430965",
  //   "96549874",
  //   "45678903",
  //   "32019012",
  //   "01329801",
  //   "10456732",
  // };
  cout << solve_day10_pt1(input) << endl;

  return 0;
}
