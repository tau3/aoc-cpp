#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "util.hpp"

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

vector<string> split(const string &line) {
  vector<string> result;
  stringstream stream(line);
  string word;
  while (stream >> word) {
    result.push_back(word);
  }
  return result;
}

