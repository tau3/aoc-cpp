#include "day3.hpp"
#include "util.hpp"
#include <cctype>
#include <cstddef>
#include <iostream>
#include <regex>

// mul(123,4)
int calc_single_mul(const string &input) {
  cout << "mul input: " << input << endl;	
  std::regex mul("mul\\(([0-9]{1,3}),([0-9]{1,3})\\).*");
  std::smatch pieces_match;
  if (!std::regex_match(input, pieces_match, mul)) {
    // cout << "input does not match" << endl;
    return 0;
  }
  // cout << "raw left:" << pieces_match[1] << endl;
  int left = stoi(pieces_match[1]);
  int right = stoi(pieces_match[2]);

  // cout << "left=" << left << "; right=" << right << endl;
  return left * right;
}

int solve(string input) {
  int result = 0;
  for (size_t i = 0; i < input.size();) {
    size_t loc = input.find("mul(", i);
    if (loc != string::npos) {
      input = input.substr(loc);
      result += calc_single_mul(input);
      // i = loc;
    } else {
      break;
    }
  }
  return result;
}
