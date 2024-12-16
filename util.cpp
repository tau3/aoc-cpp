#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "util.hpp"

using namespace std;

template <typename T>
bool contains(const std::vector<T> &values, const T &val) {
  return find(values.begin(), values.end(), val) != values.end();
}

vector<string> read_file(const string &path) {
  vector<string> lines;
  ifstream input(path);
  string line;
  while (getline(input, line)) {
    lines.push_back(line);
  }
  return lines;
}

bool starts_with(const string &input, const string &prefix) {
  return input.rfind(prefix, 0) == 0;
}

vector<string> split(const string &line, const string &delimiter) {

  vector<string> result;
  size_t last = 0;
  size_t next = 0;
  while ((next = line.find(delimiter, last)) != string::npos) {
    const string token = line.substr(last, next - last);
    result.push_back(token);
    last = next + 1;
  }
  result.push_back(line.substr(last));
  return result;
}
