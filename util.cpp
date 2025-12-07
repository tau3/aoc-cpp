#include "util.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

namespace util {

using namespace std;

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
    last = next + delimiter.size();
  }
  result.push_back(line.substr(last));
  return result;
}

vector<string> split_by_spaces(const string &line) {
  std::stringstream ss(line);
  std::string word;

  vector<string> result;
  while (ss >> word) {
    result.push_back(word);
  }
  return result;
}

} // namespace util
