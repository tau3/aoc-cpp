#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;

int solve(const vector<string> &lines);
bool parse_line(const string &line);
vector<string> split(const string &line);

int main() {
  const vector<string> lines = {
      "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green",
      "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue",
      "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 "
      "red",
      "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 "
      "red",
      "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"};

  cout << "result = " << solve(lines) << ", expected = 8" << endl;

  return 0;
}

int solve(const vector<string> &lines) {
  int result = 0;
  for (size_t i = 0; i < lines.size(); ++i) {
    const bool possible = parse_line(lines[i]);
    if (possible) {
      result += (1 + i);
    }
  }
  return result;
}

bool parse_line(const string &line) {
  const vector<string> tokens = split(line);
  for (size_t i = 2; i < tokens.size() - 1; ++i) {
    const int count = stoi(tokens[i]);
    const string color = tokens[i + 1];
    if (!(color[0] == 'r' && count <= 12) || (color[0] == 'g' && count <= 13) ||
        (color[0] == 'b' && count <= 14)) {
      return false;
    }
  }
  return true;
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
