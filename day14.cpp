#include "day14.hpp"
#include "day5.hpp"
#include <cstddef>
#include <functional>
#include <iostream>
#include <optional>
#include <unordered_map>

namespace Day14 {

using Cache = unordered_map<size_t, string>;

optional<char> has_three_row(const string &str) {
  for (size_t i = 0; i <= str.size() - 3; i++) {
    const char c1 = str[i];
    const char c2 = str[i + 1];
    const char c3 = str[i + 2];
    if ((c1 == c2) && (c2 == c3)) {
      return c1;
    }
  }
  return nullopt;
}

string calc_md5(const size_t i, const string &salt, Cache &cache,
                const function<string(const string &)> &hash) {
  string result;
  if (cache.find(i) != cache.end()) {
    result = cache.at(i);
  } else {
    result = hash(salt + to_string(i));
    cache.emplace(i, result);
  }
  return result;
}

bool has_five_row(const string &str, const char c) {
  for (size_t i = 0; i <= str.size() - 5; i++) {
    const char c1 = str[i];
    const char c2 = str[i + 1];
    const char c3 = str[i + 2];
    const char c4 = str[i + 3];
    const char c5 = str[i + 4];
    if ((c1 == c) && (c2 == c) && (c3 == c) && (c4 == c) && (c5 == c)) {
      return true;
    }
  }
  return false;
}

bool is_key(const size_t i, const string &salt, Cache &cache,
            const function<string(const string &)> &hash) {
  const string md5 = calc_md5(i, salt, cache, hash);
  const optional<char> maybe_three_row = has_three_row(md5);
  if (!maybe_three_row.has_value()) {
    return false;
  }

  const char three_row = maybe_three_row.value();
  for (size_t j = 1; j <= 1000; j++) {
    const string current_md5 = calc_md5(i + j, salt, cache, hash);
    if (has_five_row(current_md5, three_row)) {
      return true;
    }
  }

  return false;
}

size_t solve(const string &salt, const function<string(const string &)> &hash) {
  Cache cache;
  size_t i = 0;
  size_t count = 0;
  while (count < 64) {
    if (is_key(i, salt, cache, hash)) {
      count++;
    }
    i++;
  }
  return i - 1;
}

size_t solve_pt1(const string &salt) { return solve(salt, Day5::md5); }

size_t solve_pt2(const string &salt) {
  return solve(salt, [](const string &input) {
    string result = input;
    for (size_t i = 0; i <= 2016; i++) {
      result = Day5::md5(result);
    }
    return result;
  });
}

} // namespace Day14
