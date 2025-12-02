#include "day1.hpp"

namespace Day1 {

int apply(const int, const string &);

int solve_day1_pt1(const vector<string> &rotations) {
  int current = 50;
  int result = 0;
  for (const string &rotation : rotations) {
    current = apply(current, rotation);
    if (current == 0) {
      ++result;
    }
  }
  return result;
}

int apply(const int current, const string &rotation) {
  const int direction = (rotation[0] == 'L') ? -1 : 1;
  int amount = stoi(rotation.substr(1));
  amount %= 99;
  amount *= direction;
  int result = current + amount;
  return result %= 99;
}

} // namespace Day1
