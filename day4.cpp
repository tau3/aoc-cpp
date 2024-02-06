#include "day4.hpp"
#include "util.hpp"

#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

vector<int> count_wins(const vector<string> &lines) {
  vector<int> result;
  for (const string &line : lines) {
    vector<int> winning;
    vector<int> you_have;
    vector<int> *receiver = &winning;
    const vector<string> tokens = split(line);
    for (size_t i = 2; i < tokens.size(); ++i) {
      const string &token = tokens[i];
      if (token == "|") {
        receiver = &you_have;
        continue;
      }
      int num = stoi(token);
      receiver->push_back(num);
    }

    vector<int> you_have_winning;
    sort(winning.begin(), winning.end());
    sort(you_have.begin(), you_have.end());
    set_intersection(winning.begin(), winning.end(), you_have.begin(),
                     you_have.end(), back_inserter(you_have_winning));

    int subresult = you_have_winning.size();

    result.push_back(subresult);
  }
  return result;
}

int solve_day4_pt1(const vector<string> &lines) {
  const vector<int> wins = count_wins(lines);
  int result = 0;
  for (int win : wins) {
    int subresult = (win == 0) ? 0 : pow(2, win - 1);
    result += subresult;
  }
  return result;
}

int solve_day4_pt2(const vector<string> &lines) {
  const vector<int> wins = count_wins(lines);
  vector<int> counts = vector(wins.size(), 1);
  for (size_t i = 0; i < wins.size(); ++i) {
    int win = wins[i];
    for (int j = 0; j < win; ++j) {
      counts[i + 1 + j] += 1;
    }
  }
  int result = 0;
  for (int count : counts) {
    result += count;
  }
  return result;
}

void test() {
  const vector<string> input = {
      "Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53",
      "Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19",
      "Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1",
      "Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83",
      "Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36",
      "Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11",
  };
  // cout << solve_day4_pt1(input) << " expected 13" endl;
}
