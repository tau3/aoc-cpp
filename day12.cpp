#include "day12.hpp"
#include "util.hpp"
#include <unordered_map>

namespace Day12 {

using namespace std;

class Machine {
private:
  unordered_map<string, int> registers;
  vector<string> program;
  size_t rip;

  Machine() = delete;

  void cpy(const string &from, const string &to) {
    if (from == "a" || from == "b" || from == "c" || from == "d") {
      registers[to] = registers.at(from);
    } else {
      const int val = stoi(from);
      registers[to] = val;
    }
    rip++;
  }

  void inc(const string &reg) {
    registers[reg]++;
    rip++;
  }

  void dec(const string &reg) {
    registers[reg]--;
    rip++;
  }

  void jnz(const string &reg, const int jump) {
    int val;
    if (reg == "a" || reg == "b" || reg == "c" || reg == "d") {
      val = registers.at(reg);
    } else {
      val = stoi(reg);
    }
    if (val != 0) {
      rip += jump;
    } else {
      rip++;
    }
  }

  void run_command() {
    // cout << '[' << rip << ']' << " " << program[rip] << endl;
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
      const string reg = tokens[1];
      const int jump = stoi(tokens[2]);
      jnz(reg, jump);
    }
  }

public:
  Machine(const vector<string> &program, const int c)
      : registers({
            {"a", 0},
            {"b", 0},
            {"c", c},
            {"d", 0},
        }),
        program(program), rip(0) {}

  int a() const { return registers.at("a"); }

  void run_program() {
    while (rip < program.size()) {
      run_command();
    }
  }
};

int solve_pt1(const vector<string> &input) {
  Machine machine(input, 0);
  machine.run_program();
  return machine.a();
}

int solve_pt2(const vector<string> &input) {
  Machine machine(input, 1);
  machine.run_program();
  return machine.a();
}

} // namespace Day12
