#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const int A = -1;
const int UP = -2;
const int DOWN = -3;
const int LEFT = -4;
const int RIGHT = -5;

const unordered_map<int, vector<int>> NUMERIC_KEYPAD = {
    {7, {4, 8}},       {8, {7, 9, 5}}, {9, {8, 6}}, {4, {7, 5, 1}},
    {5, {4, 8, 6, 2}}, {6, {9, 5, 3}}, {1, {2, 4}}, {2, {1, 5, 3, 0}},
    {3, {6, 2, A}},    {0, {2, A}},    {A, {3, 0}}};

const unordered_map<int, vector<int>> DIRECTIONAL_KEYPAD = {};

int to_int(const char c) {
  switch (c) {
  case 'A':
    return A;
  case '^':
    return UP;
  case '<':
    return LEFT;
  case 'v':
    return DOWN;
  case '>':
    return RIGHT;
  default:
    return c - '0';
  }
}

string process_sequence(const string &code,
                              const unordered_map<int, vector<int>> &graph) {
  int start = A;
  string result;
  for (size_t i = 0; i < code.size(); ++i) {
    int end = to_int(code[i]);
    result += shortest_path(start, end, graph);
    result += 'A';
    start = end;
  }
  return result;
}

string code_to_sequence(const string &code) {}

int complexity(const string &code) {
  string result = process_sequence(code, NUMERIC_KEYPAD);
  result = process_sequence(result, DIRECTIONAL_KEYPAD);
  result = process_sequence(result, DIRECTIONAL_KEYPAD);
  result = process_sequence(result, DIRECTIONAL_KEYPAD);

  int numeric_part = stoi(code.substr(0, code.size() - 2));
  return result.size() * numeric_part;
}

int solve(const vector<string> &input) {
  int result = 0;
  for(const string& code : input){
    result += complexity(code);
  }
  return result;
}

