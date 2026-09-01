#include "util.hpp"
#include <array>
#include <cstddef>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const size_t WIDTH = 7;
const size_t HEIGHT = 3;

using Screen = array<array<bool, WIDTH>, HEIGHT>;

void rect(Screen &screen, const size_t a, const size_t b);
void rotate_row(Screen &screen, const size_t row, const size_t shift);
void rotate_col(Screen &screen, const size_t col, const size_t shift);

size_t solve(const vector<string> &input) {
  Screen screen;

  for (const string &line : input) {
    const vector<string> tokens = util::split(line, " ");
    const string &command = tokens[0];
    if (command == "rect") {
      const string &ab = tokens[1];
      const vector<string> ab_tokens = util::split(ab, "x");
      const size_t a = stol(ab_tokens[0]);
      const size_t b = stol(ab_tokens[1]);

      rect(screen, a, b);
    } else {
      const string pos_token = tokens[2];
      const vector<string> pos_tokens = util::split(pos_token, "=");
      const size_t pos = stol(pos_tokens[1]);
      const size_t shift = stol(tokens[4]);
      const string direction = tokens[1];
      if (direction == "row") {
        rotate_row(screen, pos, shift);
      } else {
        rotate_col(screen, pos, shift);
      }
    }
  }

  size_t result = 0;
  for (const array<bool, WIDTH> line : screen) {
    for (const bool pixel : line) {
      if (pixel) {
        result++;
      }
    }
  }
  return result;
}

void rect(Screen &screen, const size_t a, const size_t b) {
  for (size_t row = 0; row < b; row++) {
    for (size_t col = 0; col < a; col++) {
      screen[row][col] = true;
    }
  }
}

void rotate_row(Screen &screen, const size_t row, const size_t shift) {
  queue<bool> q;
  for (size_t i = 0; i < WIDTH; i++) {
    q.push(screen[row][i]);
  }

  for (size_t i = 0; i < shift; i++) {
    const bool current = q.front();
    q.pop();
    q.push(current);
  }

  for (size_t i = 0; i < WIDTH; i++) {
    const bool current = q.front();
    q.pop();
    screen[row][i] = current;
  }
}

void rotate_col(Screen &screen, const size_t col, const size_t shift) {
  queue<bool> q;
  for (size_t i = 0; i < HEIGHT; i++) {
    q.push(screen[i][col]);
  }

  for (size_t i = 0; i < shift; i++) {
    const bool current = q.front();
    q.pop();
    q.push(current);
  }

  for (size_t i = 0; i < HEIGHT; i++) {
    const bool current = q.front();
    q.pop();
    screen[i][col] = current;
  }
}
