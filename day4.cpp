#include "day4.hpp"
#include "util.hpp"
#include <algorithm>
#include <cmath>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

int solve_day4_pt1(const vector<string> &lines) {
  int result = 0;
  for (const string &line : lines) {
    vector<int> winning;
    vector<int> you_have;
    vector<int> &receiver = winning;
    const vector<string> tokens = split(line);
    for (size_t i = 2; i < tokens.size(); ++i) {
      if (tokens[i] == "|") {
        receiver = you_have;
        continue;
      }
      receiver.push_back(stoi(tokens[i]));
    }

    vector<int> you_have_winning;
    set_intersection(winning.begin(), winning.end(), you_have.begin(),
                     you_have.end(), back_inserter(you_have_winning));

    result += pow(2, you_have_winning.size() - 1);
  }
  return result;
}
