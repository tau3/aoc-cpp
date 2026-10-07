#include "day23.hpp"
#include "day12.hpp"
#include "util.hpp"
#include <cassert>
#include <cstddef>
#include <format>
#include <stdexcept>
#include <vector>

namespace Day23 {

void tgl(const Day12::Machine &machine, vector<string> &program, size_t &rip);

int solve(const vector<string> &input) {
  Day12::ExtraHandlers extra_handlers = {{"tgl", tgl}};

  Day12::Machine machine(input, extra_handlers);
  machine.run_program();

  return machine.a();
}

bool is_oob(const size_t rip, const int x, const size_t program_size) {
  if (x < 0) {
    if (abs(x) > rip) {
      return true;
    }
  }

  return (rip + x) >= program_size;
}

string join(const vector<string> &tokens, const char delimiter) {
  string result = "";
  for (const string &token : tokens) {
    result += token;
    result += delimiter;
  }

  result.pop_back();
  return result;
}

int read_reg(const Day12::Machine &machine, const string &reg) {
#define READ_REG(x)                                                            \
  if (reg == #x) {                                                             \
    return machine.x();                                                        \
  }

  READ_REG(a);
  READ_REG(b);
  READ_REG(c);
  READ_REG(d);

  throw runtime_error(format("invalid reg {}", reg));
}

void tgl(const Day12::Machine &machine, vector<string> &program, size_t &rip) {
  const string &command = program[rip];

  vector<string> tokens = util::split(command, " ");
  assert(tokens[0] == "tgl");

  const string reg = tokens[1];
  const int x = read_reg(machine, reg);

  if (is_oob(rip, x, program.size())) {
    rip++;
    return;
  }

  const size_t target_rip = rip + x;
  const string &target_command = program[target_rip];
  tokens = util::split(target_command, " ");
  if (tokens.size() == 2) {
    if (tokens[0] == "inc") {
      tokens[0] = "dec";
    } else {
      tokens[0] = "inc";
    }
  } else if (tokens.size() == 3) {
    if (tokens[0] == "jnz") {
      tokens[0] = "cpy";
    } else {
      tokens[0] = "jnz";
    }
  }
  const string new_command = join(tokens, ' ');
  program[target_rip] = new_command;

  rip++;
}

} // namespace Day23
