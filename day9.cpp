#include "day9.hpp"
#include "util.hpp"

using namespace std;

int solve_line(vector<int_t> &);
bool all_zeros(const vector<int_t> &);
vector<int_t> diffs(const vector<int_t> &);
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

int_t solve(const vector<vector<int_t>> &lines) {
  int result = 0;
  for (vector<int_t> line : lines) {
    int line_result = solve_line(line);
    result += line_result;
  }
  return result;
}

int solve_line(vector<int_t> &line) {
  vector<vector<int_t>> pyramid;

  vector<int_t> current = line;
  while (!all_zeros(current)) {
    pyramid.push_back(current);
    current = diffs(current);
  }
  pyramid.push_back(current);
  last(pyramid).push_back(0);

  for (size_t i = pyramid.size() - 2; i-- > 0;) {
    int val = last(pyramid[i]) + last(pyramid[i + 1]);
    pyramid[i].push_back(val);
  }

  return last(pyramid[0]);
}

template <typename T> T last(const vector<T> &items) {
  return items[items.size() - 1];
}

vector<int_t> diffs(const vector<int_t> &line) {
  vector<int_t> result;
  for (size_t i = 1; i < line.size(); ++i) {
    result.push_back(line[i] - line[i - 1]);
  }
  return result;
}

bool all_zeros(const vector<int_t> &line) {
  for (int i : line) {
    if (i != 0) {
      return false;
    }
  }
  return true;
}
