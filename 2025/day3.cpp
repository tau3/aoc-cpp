#include "day3.hpp"
#include <cassert>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

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

const size_t BAT_LENGTH = 12;

void max_number(const string &battery, const size_t start,
                vector<string> &memo) {
  const string &prev_max = memo[start + 1];
  string current_max = prev_max;
  for (size_t i = 0; i < BAT_LENGTH; i++) {
    string copy = prev_max;
    copy.erase(i, 1);
    copy.insert(0, 1, battery[start]);
    if (copy > current_max) {
      current_max = copy;
    }
  }
  memo[start] = current_max;
}

string solve_line(const string &battery) {
  const size_t max_start = battery.length() - BAT_LENGTH;
  vector<string> memo(max_start + 1);
  memo[max_start] = battery.substr(max_start, BAT_LENGTH);
  for (int i = max_start - 1; i >= 0; i--) {
    max_number(battery, i, memo);
  }
  return memo[0];
}

long solve_day3_pt2(const vector<string> &input) {
  long result = 0;
  for (const string &battery : input) {
    const string local_max = solve_line(battery);
    result += stol(local_max);
  }
  return result;
}

} // namespace Day3
