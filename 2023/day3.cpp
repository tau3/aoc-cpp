#include "day3.hpp"
#include <vector>
#include <iostream>

using namespace std;

bool is_part_number(const vector<string> &lines, size_t y, size_t start,
                    size_t length);
bool is_digit(char ch);
bool is_symbol(char ch);

int solve_day3_pt1(const vector<string> &lines) {
  int result = 0;
  bool is_building_number = false;
  string number = "";
  const size_t width = lines[0].size();
  for (size_t y = 0; y < lines.size(); ++y) {
    if (is_building_number) {
      if (is_part_number(lines, y - 1, width, number.length())) {
        result += stoi(number);
      }
      is_building_number = false;
      number = "";
    }
    is_building_number = false;
    number = "";
    for (size_t x = 0; x < width; ++x) {
      if (is_digit(lines[y][x])) {
        if (!is_building_number) {
          is_building_number = true;
        }
        number += lines[y][x];
      } else {
        if (is_building_number) {
          if (is_part_number(lines, y, x, number.length())) {
            result += stoi(number);
          }
          is_building_number = false;
          number = "";
        }
      }
    }
  }
  return result;
}

bool is_part_number(const vector<string> &lines, size_t y, size_t x,
                    size_t length) {
  const int start = x - length;
  for (int i = std::max(0, (int)start - 1); i < start + length + 1; ++i) {
    if (y >= 1 && is_symbol(lines[y - 1][i])) {
      return true;
    }
    if (y < lines.size() - 1 && is_symbol(lines[y + 1][i])) {
      return true;
    }
  }

  return (((start > 0) && is_symbol(lines[y][start - 1])) ||
          (is_symbol(lines[y][start + length])));
}

bool is_digit(char ch) { return ch >= '0' && ch <= '9'; }

bool is_symbol(char ch) { return !is_digit(ch) && (ch != '.'); }


void test_day3_pt1() {
  // clang-format off
  const vector<string> input = {
    "467..114..",
    "...*......",
    "..35..633.",
    "......#...",
    "617*......",
    ".....+.58.",
    "..592.....",
    "......755.",
    "...$.*....",
    ".664.598.."
  };
  // clang-format on
  int actual = solve_day3_pt1(input);
  cout << "result = " << actual << endl;
}
