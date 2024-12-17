#include "day5.hpp"
#include "util.hpp"
#include <cstddef>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace Day5 {
using namespace std;

using Ordering = unordered_map<int, vector<int>>;
using Update = vector<int>;

tuple<int, int> parse_ordering(const string &line) {
  const auto tokens = split(line, "|");
  return {stoi(tokens[1]), stoi(tokens[0])};
}

Update parse_update(const string &line) {
  Update result;
  const vector<string> tokens = split(line, ",");
  for (const string &token : tokens) {
    result.push_back(stoi(token));
  }
  return result;
}

bool contains_key(const Ordering &ordering, int key) {
  return ordering.find(key) != ordering.end();
}

tuple<Ordering, vector<Update>> parse_input(const vector<string> &input) {
  Ordering ordering;
  vector<Update> updates;

  bool is_ordering = true;
  for (const string &line : input) {
    if (line.empty()) {
      is_ordering = false;
      continue;
    }

    if (is_ordering) {
      // TODO extract?
      const auto [key, value] = parse_ordering(line);
      if (contains_key(ordering, key)) {
        vector<int> &values = ordering[key];
        values.push_back(value);
      } else {
        vector<int> values = {value};
        ordering[key] = values;
      }
    } else {
      const Update update = parse_update(line);
      updates.push_back(update);
    }
  }

  return {ordering, updates};
}

bool is_valid(const Update &update, const Ordering &ordering) {
  for (size_t i = 0; i < update.size(); ++i) {
    const int num = update[i];
    if (auto entry = ordering.find(num); entry != ordering.end()) {
      const vector<int> &expected_before = entry->second;
      for (size_t j = i + 1; j < update.size(); ++j) {
        if (contains(expected_before, update[j])) {
          return false;
        }
      }
    }
  }

  return true;
}

int solve_day5_pt1(const vector<string> &input) {
  const auto [ordering, updates] = parse_input(input);

  int result = 0;
  for (const Update &update : updates) {
    if (is_valid(update, ordering)) {
      const size_t size = update.size();
      const int middle = update[size / 2];
      result += middle;
    }
  }
  return result;
}

void swap(vector<int> &values, const size_t i, const size_t j) {
  size_t temp = values[i];
  values[i] = values[j];
  values[j] = temp;
}

Update fix_update(const Update &update, const Ordering &ordering) {
  Update result = update;
  for (int i = result.size() - 1; i >= 0; --i) {
    for (size_t j = 0; j < i; ++j) {
      if (auto entry = ordering.find(result[j]); entry != ordering.end()) {
        const vector<int> &expected_before = entry->second;
        if (contains(expected_before, result[i])) {
          swap(result, j, i);
          ++i;
          break;
        }
      }
    }
  }
  return result;
}

int solve_day5_pt2(const vector<string> &input) {
  const auto [ordering, updates] = parse_input(input);

  int result = 0;
  for (const Update &update : updates) {
    if (!is_valid(update, ordering)) {
      const Update fixed = fix_update(update, ordering);
      const size_t size = fixed.size();
      const int middle = fixed[size / 2];
      result += middle;
    }
  }
  return result;
}
} // namespace Day5
