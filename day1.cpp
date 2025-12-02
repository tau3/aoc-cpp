#include "day1.hpp"
#include <iostream>
#include <string>

namespace Day1 {

int apply_pt1(const int, const string &);
int apply_pt2(const int, const string &);

int solve(const vector<string> &rotations,
          int (*apply)(const int, const string &)) {
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

int solve_day1_pt1(const vector<string> &rotations) {
  return solve(rotations, apply_pt1);
}

int solve_day1_pt2(const vector<string> &rotations) {
  return solve(rotations, apply_pt2);
}

int apply_pt1(const int current, const string &rotation) {
  int amount = stoi(rotation.substr(1));
  const int direction = (rotation[0] == 'L') ? -1 : 1;
  amount %= 100;
  amount *= direction;
  int result = current + amount;
  if (result < 0) {
    result = 99 + result + 1;
  } else if (result > 99) {
    result = result - 99 - 1;
  }
  return result;
}

int apply_pt2(const int current, const string &rotation) {
  int amount = stoi(rotation.substr(1));
  const int direction = (rotation[0] == 'L') ? -1 : 1;
  amount %= 100;
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
