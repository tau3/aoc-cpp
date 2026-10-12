#include "day12.hpp"
#include "util.hpp"
#include <cassert>
#include <format>
#include <stdexcept>
#include <unordered_map>

namespace Day12 {

using namespace std;

void Machine::cpy(const string &from, const string &to) {
  if (from == "a" || from == "b" || from == "c" || from == "d") {
    registers[to] = registers.at(from);
  } else {
    const int val = stoi(from);
    registers[to] = val;
  }
  rip++;
}

void Machine::inc(const string &reg) {
  registers[reg]++;
  rip++;
}

void Machine::dec(const string &reg) {
  registers[reg]--;
  rip++;
}

void Machine::jnz(const string &x, const string &y) {
  int test_val;
  if (x == "a" || x == "b" || x == "c" || x == "d") {
    test_val = registers.at(x);
  } else {
    test_val = stoi(x);
  }

  if (test_val == 0) {
    rip++;
    return;
  }

  int jump;
  if (y == "a" || y == "b" || y == "c" || y == "d") {
    jump = registers.at(y);
  } else {
    jump = stoi(y);
  }

  rip += jump;
}

void Machine::run_command() {
  const vector<string> tokens = util::split(program[rip], " ");
  const string command = tokens[0];

  if (command == "cpy") {
    const string from = tokens[1];
    const string to = tokens[2];
    cpy(from, to);
  } else if (command == "inc") {
    const string reg = tokens[1];
    inc(reg);
  } else if (command == "dec") {
    const string reg = tokens[1];
    dec(reg);
  } else if (command == "jnz") {
    const string x = tokens[1];
    const string y = tokens[2];
    jnz(x, y);
  } else {
    const auto e = extra_handlers.find(command);
    if (e == extra_handlers.end()) {
      throw runtime_error(format("unknown command: {}", command));
    }
    const auto handler = e->second;
    handler(*this, program, rip);
  }
}

Machine::Machine(const vector<string> &program,
                 const unordered_map<string, int> &registers,
                 const ExtraHandlers &extra_handlers)
    : registers(registers), program(program), rip(0),
      extra_handlers(extra_handlers) {
  assert(registers.size() == 4);
  assert(registers.find("a") != registers.end());
  assert(registers.find("b") != registers.end());
  assert(registers.find("c") != registers.end());
  assert(registers.find("d") != registers.end());
}

void Machine::run_program() {
  while (rip < program.size()) {
    run_command();
  }
}

int solve_pt1(const vector<string> &input) {
  Machine machine(input, Machine::default_registers(), {});
  machine.run_program();
  return machine.a();
}

int solve_pt2(const vector<string> &input) {
  const unordered_map<string, int> registers{
      {"a", 0},
      {"b", 0},
      {"c", 1},
      {"d", 0},
  };
  Machine machine(input, registers, {});
  machine.run_program();
  return machine.a();
}

} // namespace Day12
