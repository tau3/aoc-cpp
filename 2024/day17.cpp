#include "util.hpp"
#include <cassert>
#include <cmath>
#include <string>
#include <tuple>
#include <vector>

namespace Day17 {

using namespace std;

using r_type = int64_t;
static_assert(std::is_signed_v<r_type> == true);

class Computer {
  Computer() {};
  r_type a;
  r_type b;
  r_type c;
  vector<r_type> out_stream;
  r_type pointer;
  vector<r_type> program;

  r_type eval_combo_operand(const r_type operand) {
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

  void adv(const r_type operand) {
    a = a / (pow(2, eval_combo_operand(operand)));
  }

  void bxl(const r_type operand) { b ^= operand; }

  void bst(const r_type operand) { b = eval_combo_operand(operand) % 8; }

  void jnz(const r_type operand) {
    if (a == 0) {
      pointer += 2;
      return;
    }

    pointer = operand;
  }

  void bxc(const r_type operand) { b ^= c; }

  void out(const r_type operand) {
    r_type result = eval_combo_operand(operand) % 8;
    out_stream.push_back(result);
  }

  void bdv(const r_type operand) {
    b = a / (pow(2, eval_combo_operand(operand)));
  }

  void cdv(const r_type operand) {
    c = a / (pow(2, eval_combo_operand(operand)));
  }

  void exec(const r_type opcode, const r_type operand) {
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
    default:
      throw "unreachable";
    }
  }

public:
  Computer(const r_type a, const r_type b, const r_type c,
           const vector<r_type> program)
      : a(a), b(b), c(c), pointer(0), program(program) {}

  void run() {
    while (pointer < program.size()) {
      exec(program[pointer], program[pointer + 1]);
    }
  }

  const vector<r_type> &out_values() const { return out_stream; }

  string output() const {
    string result = ",";
    for (const r_type val : out_stream) {
      result += to_string(val);
      result += ",";
    }
    return result;
  }
};

pair<tuple<r_type, r_type, r_type>, vector<r_type>>
parse_input(const vector<string> &input) {
  const auto a_raw = split(input[0], " ");
  const auto b_raw = split(input[1], " ");
  const auto c_raw = split(input[2], " ");
  auto program_raw = split(input[4], " ");

  r_type a = stol(a_raw[2]);
  r_type b = stol(b_raw[2]);
  r_type c = stol(c_raw[2]);

  program_raw = split(program_raw[1], ",");
  vector<r_type> program;
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

// stolen here: https://www.bytesizego.com/blog/aoc-day17-golang
r_type solve_day17_pt2(const vector<string> &input) {
  const auto [registers, program] = parse_input(input);
  auto [_, b, c] = registers;
  r_type a = 1;

  while (true) {
    Computer comp(a, b, c, program);
    comp.run();
    vector<r_type> out = comp.out_values();
    if (out == program) {
      return a;
    }

    if (out.size() < program.size()) {
      a *= 2;
      assert(a > 0);
      continue;
    }

    for (r_type i = program.size() - 1; i >= 0; --i) {
      if (program[i] != out[i]) {
        a += pow(8, i);
        break;
      }
    }
  }
}

} // namespace Day17
