#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> read_file(const std::string &);

std::vector<std::string> split(const std::string &, const std::string &);

template <typename T>
bool contains(const std::vector<T> &values, const T &val) {
  return find(values.begin(), values.end(), val) != values.end();
}

bool starts_with(const std::string &, const std::string &);

template <typename T> void print(const T &items) {
  std::cout << "vector: ";
  for (const auto &item : items) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}

template <typename T> std::string to_string(const T &items) {
  std::string result = "vector: ";

  for (const auto &item : items) {
    result += item;
    result += " ";
  }
  return result;
}
