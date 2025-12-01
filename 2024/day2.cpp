#include "day2.hpp"
#include "util.hpp"
#include <cstddef>
#include <cstdlib>
#include <vector>

bool is_safe_pt1(const vector<int> &report) {
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

void drop(vector<int> &items, const size_t index) {
  items.erase(items.begin() + index);
}

bool is_safe_pt2(const vector<int> &report) {
  if (is_safe_pt1(report)) {
    return true;
  }

  for (size_t i = 0; i < report.size(); ++i) {
    vector<int> current = report;
    drop(current, i);
    if (is_safe_pt1(current)) {
      return true;
    }
  }

  return false;
}

int solve(const vector<string> &input, const bool is_pt_1) {
  int result = 0;
  for (const string &line : input) {
    const vector<string> levels = split(line, " ");
    vector<int> report;
    for (const string &level : levels) {
      report.push_back(stoi(level));
    }

    if ((is_pt_1 && (is_safe_pt1(report))) || is_safe_pt2(report)) {
      ++result;
    }
  }
  return result;
}

int solve_day2_pt1(const vector<string> &input) { return solve(input, true); }

int solve_day2_pt2(const vector<string> &input) { return solve(input, false); }
