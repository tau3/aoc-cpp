#include "day14.hpp"
#include "util.hpp"
#include <iostream>
#include <ostream>

using namespace std;
using namespace Day14;

int main() {
  // const vector<string> input = read_file("../day14_input");
  // clang-format off
  const vector<string> input = {
    "p=0,4 v=3,-3",
    "p=6,3 v=-1,-3",
    "p=10,3 v=-1,2",
    "p=2,0 v=2,-1",
    "p=0,0 v=1,3",
    "p=3,0 v=-2,-2",
    "p=7,6 v=-1,-3",
    "p=3,0 v=-1,-2",
    "p=9,3 v=2,3",
    "p=7,3 v=-1,2",
    "p=2,4 v=2,-3",
    "p=9,5 v=-3,-3",
  };
  // clang-format on

  // Robot robot{{2,4}, {2,-3}};
  // Grid grid {11,7};
  // robot.move(grid);
  // cout << "(" << robot.position.x << "," << robot.position.y << ")" << endl;
  // robot.move(grid);
  // cout << "(" << robot.position.x << "," << robot.position.y << ")" << endl;
  // robot.move(grid);
  // cout << "(" << robot.position.x << "," << robot.position.y << ")" << endl;
  // robot.move(grid);
  // cout << "(" << robot.position.x << "," << robot.position.y << ")" << endl;
  // robot.move(grid);
  // cout << "(" << robot.position.x << "," << robot.position.y << ")" << endl;

  Robot robot{{5, 0}, {0, 0}};
  Grid grid{11, 7};
  cout << "q: " << robot.quadrant(grid) << endl;

  // cout << solve_raw_input(input, {11, 7}) << endl;

  return 0;
}
