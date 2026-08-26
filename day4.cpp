#include "day4.hpp"
#include "util.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <vector>

#define DEBUG 1

namespace Day4 {

pair<int, string> parse_sector_and_hash(const vector<string> &tokens) {
  const string last = tokens[tokens.size() - 1];

  int sector_id = 0;
  string checksum = "";
  bool is_checksum = false;
  for (size_t i = 0; i < last.size() - 1; i++) {
    char current = last[i];
    if (last[i] == '[') {
      is_checksum = true;
      continue;
    }

    if (is_checksum) {
      checksum += current;
    } else {
      sector_id *= 10;
      sector_id += (current - '0');
    }
  }

  return {sector_id, checksum};
}

static const size_t ENGLISH_LETTERS = 26;
static const size_t CHECKSUM_LENGTH = 5;
using Checksum = array<pair<char, size_t>, ENGLISH_LETTERS>;

#ifdef DEBUG

string print_checksum(const Checksum &checksum) {
  string result = "";
  for (size_t i = 0; i < CHECKSUM_LENGTH; i++) {
    result += checksum[i].first;
  }
  return result;
}

#endif

Checksum calc_actual_checksum(const vector<string> &tokens) {
  array<size_t, ENGLISH_LETTERS> counter = {};
  for (size_t i = 0; i < tokens.size() - 1; i++) {
    for (const char current : tokens[i]) {
      counter[current - 'a']++;
    }
  }

  Checksum named_counter;
  for (size_t i = 0; i < ENGLISH_LETTERS; i++) {
    named_counter[i] = {'a' + i, counter[i]};
  }

  sort(named_counter.begin(), named_counter.end(),
       [](const pair<char, size_t> left, const pair<char, size_t> right) {
         if (left.second > right.second) {
           return true;
         }
         if (left.second < right.second) {
           return false;
         }
         return left.first < right.first;
       });

  return named_counter;
}

bool is_valid_checksum(const string &expected_hashsum,
                       const Checksum actual_checksum) {
  bool result = true;
  for (size_t i = 0; i < CHECKSUM_LENGTH; i++) {
    if (actual_checksum[i].first != expected_hashsum[i]) {
      result = false;
      break;
    }
  }
  return result;
}

int solve_day4_pt1(const vector<string> &input) {
  int result = 0;
  for (const string &room : input) {
    const vector<string> tokens = util::split(room, "-");

    const auto [sector_id, expected_checksum] = parse_sector_and_hash(tokens);
    const Checksum actual_checksum = calc_actual_checksum(tokens);

#ifdef DEBUG
    cout << "sector " << sector_id << " expected checksum " << expected_checksum
         << "; actual checksum " << print_checksum(actual_checksum) << endl;
#endif

    if (is_valid_checksum(expected_checksum, actual_checksum)) {
      result += sector_id;
    }
  }

  return result;
}

} // namespace Day4
