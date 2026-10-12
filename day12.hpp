#ifndef INCLUDE_DAY_12_H
#define INCLUDE_DAY_12_H

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Day12 {

using namespace std;

int solve_pt1(const vector<string> &input);
int solve_pt2(const vector<string> &input);

class Machine;

using ExtraHander = function<void(const Machine &machine,
                                  vector<string> &program, size_t &rip)>;
using ExtraHandlers = unordered_map<string, ExtraHander>;

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
  void jnz(const string &x, const string &y);

public:
  explicit Machine(const vector<string> &program,
                   const unordered_map<string, int> &registers,
                   const ExtraHandlers &extra_handlers);

  static unordered_map<string, int> default_registers() {
    const static unordered_map<string, int> result = {
        {"a", 0}, {"b", 0}, {"c", 0}, {"d", 0}};
    return result;
  }

  void run_program();
  void run_command();

#define REG_FUN(x)                                                             \
  inline int x() const { return registers.at(#x); }

  REG_FUN(a)
  REG_FUN(b)
  REG_FUN(c)
  REG_FUN(d)
};

} // namespace Day12

#endif
