#include "util.hpp"
#include <cstddef>
#include <string>
#include <vector>

namespace Day25 {

using namespace std;

const size_t MAX_HEIGHT = 7;

vector<size_t> lock_to_heights(const vector<string> &lock) {
  vector<size_t> result;

  for (size_t col = 0; col < lock[0].size(); ++col) {
    for (size_t row = 0; row < lock.size(); ++row) {
      if (lock[row][col] == '.') {
        result.push_back(row - 1);
        break;
      }
    }
  }
  return result;
}

vector<size_t> key_to_heights(const vector<string> &key) {
  vector<size_t> result;

  for (size_t col = 0; col < key[0].size(); ++col) {
    for (size_t row = 0; row < key.size(); ++row) {
      if (key[row][col] == '#') {
        result.push_back(MAX_HEIGHT - row - 1);
        break;
      }
    }
  }
  return result;
}

bool is_fit(const vector<size_t> &lock, const vector<size_t> &key) {
  for (size_t i = 0; i < lock.size(); ++i) {
    if ((lock[i] + key[i] + 2) > MAX_HEIGHT) {
      return false;
    }
  }
  return true;
}

bool is_key(const vector<string> &item) {
  const string head = item[0];
  for (size_t i = 0; i < head.size(); ++i) {
    if (head[i] == '#') {
      return false;
    }
  }
  return true;
}

int solve_day25_pt1(const vector<string> &input) {
  size_t i = 0;
  vector<vector<size_t>> keys;
  vector<vector<size_t>> locks;
  while (i < input.size()) {
    vector<string> item;
    for (size_t j = i; (j < (i + MAX_HEIGHT)) && (j < input.size()); ++j) {
      item.push_back(input[j]);
    }
    if (is_key(item)) {
      keys.push_back(key_to_heights(item));
    } else {
      locks.push_back(lock_to_heights(item));
    }
    i += MAX_HEIGHT + 1;
  }

  int result = 0;
  for (const auto &lock : locks) {
    for (const auto &key : keys) {
      if (is_fit(lock, key)) {
        ++result;
      }
    }
  }
  return result;
}

} // namespace Day25
