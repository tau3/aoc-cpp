#include "day1.hpp"
#include "util.hpp"
#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

tuple<vector<int>, vector<int>> parse_input(const vector<string> &input) {
  vector<int> left, right;
  for (const string &line : input) {
    const vector<string> tokens = split(line, "   ");
    left.push_back(stoi(tokens[0]));
    right.push_back(stoi(tokens[1]));
  }
  return {left, right};
}

int solve_day1_pt1(const vector<string> &input) {
  auto [left, right] = parse_input(input);

  sort(left.begin(), left.end());
  sort(right.begin(), right.end());

  int result = 0;
  for (size_t i = 0; i < left.size(); ++i) {
    int l = left[i];
    int r = right[i];
    int diff = l - r;
    if (diff < 0) {
      diff = -diff;
    }
    result += diff;
  }

  return result;
}

int solve_day1_pt2(const vector<string> &input) {
  auto [left, right] = parse_input(input);

  int result = 0;
  for (const int l : left) {
    // TODO hashmap?
    int score = count(right.begin(), right.end(), l);
    result += l * score;
  }

  return result;
}
