#include "day6.hpp"
#include "util.hpp"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>

namespace Day6 {

uint64_t solve_day6_pt1(const vector<string> &input) {
  vector<vector<string>> tokenized;
  for (const string &line : input) {
    vector<string> tokens = util::split_by_spaces(line);
    tokenized.push_back(tokens);
  };
  uint64_t result = 0;
  for (size_t i = 0; i < tokenized[0].size(); i++) {
    const string operation = tokenized[tokenized.size() - 1][i];
    uint64_t subresult = (operation == "+") ? 0 : 1;
    for (size_t j = 0; j < tokenized.size() - 1; j++) {
      const uint64_t num = stoi(tokenized[j][i]);
      subresult = (operation == "+") ? (subresult + num) : (subresult * num);
    }
    result += subresult;
  }
  return result;
}

bool is_all_spaces(const vector<string> &input, const size_t column) {
  for (size_t i = 0; i < input.size(); i++) {
    if (input[i][column] != ' ') {
      return false;
    }
  }
  return true;
}

int to_number(const vector<string> &input, const size_t column) {
  string result = "";
  for (size_t i = 0; i < input.size() - 1; i++) {
    result += input[i][column];
  }
  return stoi(result);
}

uint64_t process(const vector<string> &input, int start, int end_exclusive) {
  assert(start > end_exclusive);

  vector<int> numbers;
  char operation = ' ';
  for (int i = start; i > end_exclusive; i--) {
    numbers.push_back(to_number(input, i));
    if (operation == ' ') {
      const char possible_operation = input[input.size() - 1][i];
      if (possible_operation != ' ') {
        operation = possible_operation;
      }
    }
  }

  uint64_t result = (operation == '+') ? 0 : 1;
  for (size_t i = 0; i < numbers.size(); i++) {
    const int num = numbers[i];
    result = (operation == '+') ? (result + num) : (result * num);
  }
  return result;
}

uint64_t solve_day6_pt2(const vector<string> &input) {
  uint64_t result = 0;
  int start = input.size() - 1;
  int end_exclusive = start;
  for (size_t i = start; i >= 0; i--) {
    if (is_all_spaces(input, i)) {
      end_exclusive = i;
      result += process(input, start, end_exclusive);
      i--;
      start = i;
      end_exclusive = start;
    }
  }
  result += process(input, start, -1);
  return result;
}

} // namespace Day6
