#include "day9.hpp"
#include "util.hpp"
#include <deque>
#include <type_traits>
#include <vector>

using namespace std;

int solve_line(deque<int_t> &, bool);
bool all_zeros(const deque<int_t> &);
deque<int_t> diffs(const deque<int_t> &);
template <typename T> T last(const vector<T> &);

vector<vector<int_t>> parse(const vector<string> &input) {
  vector<vector<int_t>> result;
  for (const string &line : input) {
    const vector<string> &tokens = split(line);
    vector<int_t> ints;
    for (const string &token : tokens) {
      int val = stoi(token);
      ints.push_back(val);
    }
    result.push_back(ints);
  }
  return result;
}

deque<int_t> to_deque(const vector<int_t> &values) {
  deque<int_t> result;
  for (int_t value : values) {
    result.push_back(value);
  }
  return result;
}

int_t solve(const vector<vector<int_t>> &lines, bool right) {
  int result = 0;
  for (vector<int_t> line : lines) {
    deque<int_t> dq = to_deque(line);
    int_t line_result = solve_line(dq, right);
    result += line_result;
  }
  return result;
}

int_t solve_pt1(const std::vector<std::vector<int_t>> &lines) {
  return solve(lines, true);
}

int_t solve_pt2(const std::vector<std::vector<int_t>> &lines) {
  return solve(lines, false);
}

int solve_line(deque<int_t> &line, bool right) {
  vector<deque<int_t>> pyramid;

  deque<int_t> current = line;
  while (!all_zeros(current)) {
    pyramid.push_back(current);
    current = diffs(current);
  }
  pyramid.push_back(current);
  last(pyramid).push_back(0);

  for (size_t i = pyramid.size() - 2; i-- > 0;) {
    if (right) {
      int val = pyramid[i].back() + pyramid[i + 1].back();
      pyramid[i].push_back(val);
    } else {
      int val = pyramid[i][0] - pyramid[i + 1][0];
      pyramid[i].push_front(val);
    }
  }

  return pyramid[0].back();
}

template <typename T> T last(const vector<T> &items) {
  return items[items.size() - 1];
}

deque<int_t> diffs(const deque<int_t> &line) {
  deque<int_t> result;
  for (size_t i = 1; i < line.size(); ++i) {
    result.push_back(line[i] - line[i - 1]);
  }
  return result;
}

bool all_zeros(const deque<int_t> &line) {
  for (int i : line) {
    if (i != 0) {
      return false;
    }
  }
  return true;
}
