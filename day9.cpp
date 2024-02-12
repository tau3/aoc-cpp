#include "day9.hpp"
#include "util.hpp"

using namespace std;

int solve_line(vector<int> &);
bool all_zeros(const vector<int> &);
vector<int> diffs(const vector<int> &);
template <typename T> T last(const vector<T> &);

vector<vector<int>> parse(const vector<string> &input) {
  vector<vector<int>> result;
  for (const string &line : input) {
    const vector<string> &tokens = split(line);
    vector<int> ints;
    for (const string &token : tokens) {
      int val = stoi(token);
      ints.push_back(val);
    }
    result.push_back(ints);
  }
  return result;
}

int solve(const vector<vector<int>> &lines) {
  int result = 0;
  for (vector<int> line : lines) {
    result += solve_line(line);
  }
  return result;
}

int solve_line(vector<int> &line) {
  vector<vector<int>> pyramid;

  vector<int> *current = &line;
  while (!all_zeros(*current)) {
    pyramid.push_back(*current);
    vector<int> new_current = diffs(*current);
    current = &new_current;
  }
  last(pyramid).push_back(0);

  for (size_t i = pyramid.size() - 2; i >= 0; --i) {
    int val = last(pyramid[i]) + last(pyramid[i + 1]);
    pyramid[i].push_back(val);
  }

  return last(pyramid[0]);
}

template <typename T> T last(const vector<T> &items) {
  return items[items.size() - 1];
}

vector<int> diffs(const vector<int> &line) {
  vector<int> result;
  for (size_t i = 1; i < line.size() - 1; ++i) {
    result.push_back(line[i + 1] - line[i]);
  }
  return result;
}

bool all_zeros(const vector<int> &line) {
  for (int i : line) {
    if (i != 0) {
      return false;
    }
  }
  return true;
}
