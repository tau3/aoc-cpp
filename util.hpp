#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> read_file(const std::string &);

std::vector<std::string> split(const std::string &, const std::string &);

bool starts_with(const std::string &, const std::string &);

template <typename T> void print(const T &items) {
  std::cout << "vector: ";
  for (const auto &item : items) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}
