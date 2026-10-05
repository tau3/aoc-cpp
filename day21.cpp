#include "day21.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string>

namespace Day21 {

void swap_position(string &pass, const size_t x, const size_t y);
void swap_letter(string &pass, const char x, const char y);
void reverse_positions(string &pass, const size_t x, const size_t y);
void move_position(string &pass, const size_t x, const size_t y);
void rotate_based(string &pass, const char x);
void rotate(string &pass, const bool is_left, size_t x);

void un_swap_position(string &pass, const size_t x, const size_t y) {
  swap_position(pass, y, x);
}

void un_swap_letter(string &pass, const char x, const char y) {
  swap_letter(pass, y, x);
}

void un_reverse_positions(string &pass, const size_t x, const size_t y) {
  reverse_positions(pass, x, y);
}

void un_move_position(string &pass, const size_t x, const size_t y) {
  move_position(pass, y, x);
}

void un_rotate_based(string &pass, const char x) {
  string result = pass;
  string rotated;

  do {
    rotate(result, true, 1);
    rotated = result;
    rotate_based(rotated, x);
  } while (rotated != pass);
  pass = result;
}

void un_rotate(string &pass, const bool is_left, size_t x) {
  rotate(pass, !is_left, x);
}

void exec(string &pass, const string &command, bool is_reverse) {
  const vector<string> tokens = util::split(command, " ");
  if (util::starts_with(command, "swap position")) {
    const size_t x = stol(tokens[2]);
    const size_t y = stol(tokens[5]);
    if (!is_reverse) {
      swap_position(pass, x, y);
    } else {
      un_swap_position(pass, x, y);
    }
  } else if (util::starts_with(command, "swap letter")) {
    const char x = tokens[2][0];
    const char y = tokens[5][0];
    if (!is_reverse) {
      swap_letter(pass, x, y);
    } else {
      un_swap_letter(pass, x, y);
    }
  } else if (util::starts_with(command, "reverse positions")) {
    const size_t x = stol(tokens[2]);
    const size_t y = stol(tokens[4]);
    if (!is_reverse) {
      reverse_positions(pass, x, y);
    } else {
      un_reverse_positions(pass, x, y);
    }
  } else if (util::starts_with(command, "move position")) {
    const size_t x = stol(tokens[2]);
    const size_t y = stol(tokens[5]);
    if (!is_reverse) {
      move_position(pass, x, y);
    } else {
      un_move_position(pass, x, y);
    }
  } else if (util::starts_with(command, "rotate based")) {
    const char x = tokens[6][0];
    if (!is_reverse) {
      rotate_based(pass, x);
    } else {
      un_rotate_based(pass, x);
    }
  } else {
    const bool is_left = tokens[1] == "left";
    const size_t x = stol(tokens[2]);
    if (!is_reverse) {
      rotate(pass, is_left, x);
    } else {
      un_rotate(pass, is_left, x);
    }
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

  std::reverse(pass.begin() + x, pass.begin() + y + 1);
}

void move_position(string &pass, const size_t x, const size_t y) {
  const size_t size = pass.size();
  assert(x < size && y < size);

  const char c = pass[x];
  pass.erase(x, 1);
  pass.insert(pass.begin() + y, c);
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
  pass.erase(0, 1);
  return result;
}

char pop_last(string &pass) {
  const size_t size = pass.size();
  assert(size != 0);

  const char result = pass.back();
  pass.pop_back();
  return result;
}

string solve_pt1(const string &pass, const vector<string> &commands) {
  string result = pass;
  for (const string &command : commands) {
    exec(result, command, false);
    cout << command << " --> " << result << endl;
  }
  return result;
}

string solve_pt2(const string &pass, const vector<string> &commands) {
  string result = pass;
  for (auto rit = commands.rbegin(); rit != commands.rend(); ++rit) {
    const string command = *rit;
    exec(result, command, true);
    cout << command << " --> " << result << endl;
  }
  return result;
}

} // namespace Day21
