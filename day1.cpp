#include "day1.hpp"
#include <iostream>

namespace Day1 {

int apply(const int, const string &);

int solve_day1_pt1(const vector<string> &rotations) {
  int current = 50;
  int result = 0;
  for (const string &rotation : rotations) {
    current = apply(current, rotation);
    cout << rotation << ' ' << current << endl;
    if (current == 0) {
      ++result;
    }
  }
  return result;
}

int apply(const int current, const string &rotation) {
  int amount = stoi(rotation.substr(1));
  // if (amount == 99) {
    // return current;
  // }
  
  const int direction = (rotation[0] == 'L') ? -1 : 1;
  amount %= 99;
  amount *= direction;
  int result = current + amount;
  if (result < 0) {
    result = 99 + result + 1;
  } else if (result > 99) {
    result = result - 99 - 1;
  }
  return result;
}

} // namespace Day1
