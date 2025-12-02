#include "day1.hpp"
#include <iostream>
#include <string>

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

int solve_day1_pt2(const vector<string> &rotations) {
  int current = 50;
  int result = 0;
  for (const string &rotation : rotations) {
    int amount = stoi(rotation.substr(1));
    const int direction = (rotation[0] == 'L') ? -1 : 1;
    result += (amount / 100);
    amount %= 100;
    amount *= direction;
    current += amount;
    if (current < 0) {
      current = 99 + current + 1;
      ++result;
    } else if (current > 99) {
      current = current - 99 - 1;
      ++result;
    }
    cout << rotation << ' ' << current << endl;
    if (current == 0) {
      // ++result;
    }
  }
  return result;
}

int apply(const int current, const string &rotation) {
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
