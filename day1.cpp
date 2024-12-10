#include "day1.hpp"
#include "util.hpp"
#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

int solve_day1_pt1(vector<string> input) {
  vector<int> left, right;
  for (const string &line : input) {
    const vector<string> tokens = split(line, "   ");
    left.push_back(stoi(tokens[0]));
    right.push_back(stoi(tokens[1]));
  }

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

int solve_day1_pt2(vector<string> input) {
  vector<int> left, right;
  for (const string &line : input) {
    const vector<string> tokens = split(line, "   ");
    left.push_back(stoi(tokens[0]));
    right.push_back(stoi(tokens[1]));
  }

  int result = 0;
  for(const int l : left) {
    // TODO hashmap?
    int score = count(right.begin(), right.end(), l);
    result += score;
  }

  return result;
}

