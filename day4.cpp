#include "util.hpp"
#include <algorithm>
#include <array>
#include <cstddef>
#include <string>
#include <vector>

using namespace std;

int solve(const vector<string> &input) {
  int result = 0;
  for (const string &room : input) {
    const vector<string> tokens = util::split(room, "-");
    const string last = tokens[tokens.size() - 1];

    int sector_id = 0;
    string expected_hashsum = "";
    bool is_hashsum = false;
    for (size_t i = 0; i < last.size() - 1; i++) {
      char current = last[i];
      if (i == '[') {
        is_hashsum = true;
        continue;
      }

      if (is_hashsum) {
        expected_hashsum += current;
      } else {
        sector_id *= 10;
        sector_id += current - '0';
      }
    }

    array<size_t, 26> counter;
    for (size_t i = 0; i < tokens.size() - 1; i++) {
      for (const char current : tokens[i]) {
        counter[current - 'a']++;
      }
    }

    array<pair<char, size_t>, 26> named_counter;
    for (size_t i = 0; i < 26; i++) {
      named_counter[i] = {'a' + i, i};
    }

    sort(named_counter.begin(), named_counter.end(),
         [](const pair<char, size_t> left, const pair<char, size_t> right) {
           if (left.second > right.second) {
             return true;
           }
           if (left.second < right.second) {
             return false;
           }
           return left.first > right.first;
         });

    bool is_valid_checksum = true;
    for (size_t i = 0; i < 5; i++) {
      if (named_counter[i].first != expected_hashsum[i]) {
        is_valid_checksum = false;
        break;
      }
    }

    if (is_valid_checksum) {
      result += sector_id;
    }
  }

  return result;
}
