#include "day2.hpp"
#include "util.hpp"
#include <cstddef>
#include <cstdlib>

bool is_safe(const vector<int> &report) {
  if (report[1] == report[0]) {
    return false;
  }

  const bool is_increasing = report[1] > report[0];
  for (size_t i = 1; i < report.size(); ++i) {
    const int current = report[i];
    const int previous = report[i - 1];
    const int diff = current - previous;
    if (is_increasing) {
      if (!((diff >= 1) && (diff <= 3))) {
        return false;
      }
    } else if (!((diff <= -1) && (diff >= -3))) {
      return false;
    }
  }
  return true;
}

int solve_day2_pt1(const vector<string> &input) {
  int result = 0;
  for (const string &line : input) {
    const vector<string> levels = split(line, " ");
    vector<int> report;
    for (const string &level : levels) {
      report.push_back(stoi(level));
    }
    if (is_safe(report)) {
      ++result;
    }
  }
  return result;
}
