#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <vector>

namespace util {

std::vector<std::string> read_file(const std::string &);

std::vector<std::string> split(const std::string &, const std::string &);

template <typename T>
bool contains(const std::vector<T> &values, const T &val) {
  return find(values.begin(), values.end(), val) != values.end();
}

bool starts_with(const std::string &, const std::string &);

template <typename T> void print(const T &items) {
  std::cout << "items: ";
  for (const auto &item : items) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}

template <typename T> std::string to_str(const T &items) {
  std::string result = "items: ";
  for (const int &item : items) {
    result += std::to_string(item);
    result += " ";
  }
  return result;
}

std::vector<std::string> split_by_spaces(const std::string &);

template <typename T> struct Point {
  T row;
  T col;

  explicit Point(T row, T col) : row(row), col(col) {}
};

template <typename T>
inline bool operator==(const Point<T> &lhs, const Point<T> &rhs) {
  return (lhs.col == rhs.col) && (lhs.row == rhs.row);
}

struct PointHash {
  template <typename T> size_t operator()(const Point<T> &point) const {
    const auto [r, c] = point;
    return 31 * r + 17 * c;
  }
};

} // namespace util

#endif
