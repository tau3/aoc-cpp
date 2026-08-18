#include <climits>
#include <string>
#include <vector>

namespace Day24 {

using namespace std;

int calc_product(const vector<int> &numbers) {
  int result = 1;
  for (const int number : numbers) {
    result *= number;
  }
  return result;
}

int solve_day24_pt1(const vector<string> &input) {
  vector<int> numbers;
  int sum = 0;
  for (const string &line : input) {
    const int number = stoi(line);
    numbers.push_back(number);
    sum += number;
  }

  const int group_sum = sum / 3;

  vector<vector<int>> candidates;
  size_t min_length = numbers.size();
  for (size_t i = 1; i < 1 << numbers.size(); i++) {
    vector<int> combination;
    for (size_t j = 0; j < numbers.size(); j++) {
      if (i & (1 << j)) {
        combination.push_back(numbers[j]);
      }
    }

    int combination_sum = 0;
    for (const int j : combination) {
      combination_sum += j;
    }
    if (combination_sum == group_sum) {
      if (combination.size() == min_length) {
        candidates.push_back(combination);
      } else if (combination.size() < min_length) {
        min_length = combination.size();
        candidates.clear();
        candidates.push_back(combination);
      }
    }
  }

  int result = INT_MAX;
  for (const vector<int> &combination : candidates) {
    const int product = calc_product(combination);
    if (product < result) {
      result = product;
    }
  }

  return result;
}

} // namespace Day24
