#include "util.hpp"
#include <cassert>
#include <cmath>
#include <cstddef>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace Day17 {

using namespace std;

class Computer {
  Computer() {};
  int a;
  int b;
  int c;
  vector<int> out_stream;
  int pointer;
  vector<int> program;

  int eval_combo_operand(const int operand) {
    assert(operand >= 0 && operand < 7);

    switch (operand) {
    case 0:
    case 1:
    case 2:
    case 3:
      return operand;
    case 4:
      return a;
    case 5:
      return b;
    case 6:
      return c;
    default:
      throw "unreachable";
    }
  }

  void adv(const int operand) { a = a / (pow(2, eval_combo_operand(operand))); }

  void bxl(const int operand) { b ^= operand; }

  void bst(const int operand) { b = eval_combo_operand(operand) % 8; }

  void jnz(const int operand) {
    if (a == 0) {
      pointer += 2;
      return;
    }

    pointer = operand;
  }

  void bxc(const int operand) { b ^= c; }

  void out(const int operand) {
    int result = eval_combo_operand(operand) % 8;
    out_stream.push_back(result);
  }

  void bdv(const int operand) { b = a / (pow(2, eval_combo_operand(operand))); }

  void cdv(const int operand) { c = a / (pow(2, eval_combo_operand(operand))); }

  void exec(const int opcode, const int operand) {
    assert(opcode >= 0 && opcode <= 7);

    switch (opcode) {
    case 0:
      adv(operand);
      pointer += 2;
      break;
    case 1:
      bxl(operand);
      pointer += 2;
      break;
    case 2:
      bst(operand);
      pointer += 2;
      break;
    case 3:
      jnz(operand);
      break;
    case 4:
      bxc(operand);
      pointer += 2;
      break;
    case 5:
      out(operand);
      pointer += 2;
      break;
    case 6:
      bdv(operand);
      pointer += 2;
      break;
    case 7:
      cdv(operand);
      pointer += 2;
      break;
    }
  }

public:
  Computer(const int a, const int b, const int c, const vector<int> program)
      : a(a), b(b), c(c), pointer(0), program(program) {}

  void run() {
    while (pointer < program.size()) {
      exec(program[pointer], program[pointer + 1]);
      // dump_state();
    }
  }

  const vector<int> &out_values() const { return out_stream; }

  string output() const {
    string result = ",";
    for (const int val : out_stream) {
      result += to_string(val);
      result += ",";
    }
    return result;
  }
};

pair<tuple<int, int, int>, vector<int>>
parse_input(const vector<string> &input) {
  const auto a_raw = split(input[0], " ");
  const auto b_raw = split(input[1], " ");
  const auto c_raw = split(input[2], " ");
  auto program_raw = split(input[4], " ");

  int a = stoi(a_raw[2]);
  int b = stoi(b_raw[2]);
  int c = stoi(c_raw[2]);

  program_raw = split(program_raw[1], ",");
  vector<int> program;
  for (size_t i = 0; i < program_raw.size(); ++i) {
    program.push_back(stoi(program_raw[i]));
  }

  return {{a, b, c}, program};
}

string solve_day17_pt1(const vector<string> &input) {
  const auto [registers, program] = parse_input(input);
  const auto [a, b, c] = registers;

  Computer computer(a, b, c, program);
  computer.run();
  return computer.output();
}

int solve_day17_pt2(const vector<string> &input) {
  const auto [registers, program] = parse_input(input);
  auto [a, b, c] = registers;
  a = 1;

  Computer comp(a, b, c, program);
  comp.run();
  vector<int> out = comp.out_values();

  while (out.size() != program.size()) {
    a *= 2;
    Computer comp(a, b, c, program);
    comp.run();
    out = comp.out_values();
  }

  for (int i = program.size() - 1; i >= 0; --i) {
    if (program[i] != out[i]) {
      a += pow(8, i);
    }
  }
  return a;
}

} // namespace Day17
