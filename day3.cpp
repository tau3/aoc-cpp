#include "day3.hpp"
#include <cassert>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>

namespace Day3 {

int largest_voltage(const string &battery) {
  size_t first = string::npos;
  for (int i = 9; i >= 1; i--) {
    const size_t position = battery.find(to_string(i));
    if ((position != string::npos) && (position != (battery.length() - 1))) {
      first = position;
      break;
    }
  }

  const size_t start = first + 1;
  size_t second = string::npos;
  for (int i = 9; i >= 1; i--) {
    const size_t position = battery.find(to_string(i), start);
    if (position != string::npos) {
      second = position;
      break;
    }
  }

  assert((first != string::npos) && (second != string::npos));
  int result = (battery[first] - '0') * 10 + (battery[second] - '0');
  cout << battery << " " << result << endl;
  return result;
}

int solve_day3_pt1(const vector<string> &input) {
  int result = 0;
  for (const string &battery : input) {
    result += largest_voltage(battery);
  }
  return result;
}

} // namespace Day3
