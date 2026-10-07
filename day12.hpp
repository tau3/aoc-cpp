#ifndef INCLUDE_DAY_12_H
#define INCLUDE_DAY_12_H

#include <functional>
#include <string>
#include <vector>

namespace Day12 {

using namespace std;

int solve_pt1(const vector<string> &input);
int solve_pt2(const vector<string> &input);

class Machine;

using ExtraHandlers = unordered_map<
    string, function<void(const Machine &machine, vector<string> &, size_t &)>>;

class Machine {
private:
  unordered_map<string, int> registers;
  vector<string> program;
  size_t rip;
  ExtraHandlers extra_handlers;

  Machine() = delete;

  void cpy(const string &from, const string &to);
  void inc(const string &reg);
  void dec(const string &reg);
  void jnz(const string &x, const string& y);
  void run_command();

public:
  explicit Machine(const vector<string> program, const int c) noexcept;

  explicit Machine(const vector<string> program,
                   const ExtraHandlers extra_handlers) noexcept;

  void run_program();

#define REG_FUN(x)                                                             \
  inline int x() const { return registers.at(#x); }

  REG_FUN(a)
  REG_FUN(b)
  REG_FUN(c)
  REG_FUN(d)
};

} // namespace Day12

#endif
