#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string>

using namespace std;

void swap_position(string &pass, const size_t x, const size_t y);
void swap_letter(string &pass, const char x, const char y);
void reverse_positions(string &pass, const size_t x, const size_t y);
void move_position(string &pass, const size_t x, const size_t y);
void rotate_based(string &pass, const char x);
void rotate(string &pass, const bool is_left, size_t x);

void solve(string &pass, const string &command) {
  const vector<string> tokens = util::split(command, " ");
  if (util::starts_with(command, "swap position")) {
    const size_t x = stol(tokens[2]);
    const size_t y = stol(tokens[5]);
    swap_position(pass, x, y);
  } else if (util::starts_with(command, "swap letter")) {
    const char x = tokens[2][0];
    const char y = tokens[5][0];
    swap_letter(pass, x, y);
  } else if (util::starts_with(command, "reverse positions")) {
    const size_t x = stol(tokens[2]);
    const size_t y = stol(tokens[4]);
    reverse_positions(pass, x, y);
  } else if (util::starts_with(command, "move position")) {
    const size_t x = stol(tokens[2]);
    const size_t y = stol(tokens[5]);
    move_position(pass, x, y);
  } else if (util::starts_with(command, "rotate based")) {
    const char x = tokens[6][0];
    rotate_based(pass, x);
  } else {
    const bool is_left = tokens[1] == "left";
    const size_t x = stol(tokens[2]);
    rotate(pass, is_left, x);
  }
}

void swap_position(string &pass, const size_t x, const size_t y) {
  const size_t size = pass.size();
  assert(x < size && y < size);

  const char temp = pass[x];
  pass[x] = pass[y];
  pass[y] = temp;
}

void swap_letter(string &pass, const char x, const char y) {
  const auto x_pos = pass.find(x);
  const auto y_pos = pass.find(y);

  assert(x_pos != pass.npos && y_pos != pass.npos);

  pass[x_pos] = y;
  pass[y_pos] = x;
}

void reverse_positions(string &pass, const size_t x, const size_t y) {
  const size_t size = pass.size();
  assert(x < size && y < size);

  std::reverse(pass.begin() + x, pass.begin() + y);
}

void move_position(string &pass, const size_t x, const size_t y) {
  const size_t size = pass.size();
  assert(x < size && (y - 1) < size);

  const char c = pass[x];
  pass.erase(x, 1);
  pass.insert(pass.begin() + (y - 1), c);
}

char pop_first(string &pass);
char pop_last(string &pass);

void rotate(string &pass, const bool is_left, size_t x) {
  assert(!pass.empty());

  const size_t size = pass.size();
  x %= size;

  if (is_left) {
    for (size_t i = 0; i < x; i++) {
      const char c = pop_first(pass);
      pass += c;
    }
  } else {
    for (size_t i = 0; i < x; i++) {
      const char c = pop_last(pass);
      pass = c + pass;
    }
  }
}

void rotate_based(string &pass, const char x) {
  const auto x_pos = pass.find(x);
  assert(x_pos != pass.npos);

  rotate(pass, false, 1);
  rotate(pass, false, x_pos);
  if (x_pos >= 4) {
    rotate(pass, false, 1);
  }
}

char pop_first(string &pass) {
  assert(!pass.empty());

  const char result = pass[0];
  pass.erase(1);
  return result;
}

char pop_last(string &pass) {
  const size_t size = pass.size();
  assert(size != 0);

  const char result = pass[size - 1];
  pass.erase(size - 1, 1);
  return result;
}
