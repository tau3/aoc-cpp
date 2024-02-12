#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> read_file(const std::string &);
std::vector<std::string> split(const std::string &);
template <typename T> void print(const std::vector<T> items) {
  std::cout << "vector: ";
  for (T item : items) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}
