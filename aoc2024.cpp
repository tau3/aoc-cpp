#include "day1.hpp"
#include "util.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {
  const vector<string> input = read_file("../day1_input");
  cout << solve_day1(input) << endl;

  return 0;
}
