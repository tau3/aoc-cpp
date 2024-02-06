#include "day4.hpp"
#include "util.hpp"

#include <algorithm>
#include <cmath>

using namespace std;

int solve_day4_pt1(const vector<string> &lines) {
  int result = 0;
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

    int subresult =
        you_have_winning.empty() ? 0 : pow(2, you_have_winning.size() - 1);
    result += subresult;
  }
  return result;
}
