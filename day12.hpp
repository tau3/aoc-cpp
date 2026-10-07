#ifndef INCLUDE_DAY_12_H
#define INCLUDE_DAY_12_H

#include <functional>
#include <string>
#include <vector>

namespace Day12 {

using namespace std;

int solve_pt1(const vector<string> &input);
int solve_pt2(const vector<string> &input);

using ExtraHandlers =
    unordered_map<string, function<void(vector<string> &, const size_t)>>;

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
  void jnz(const string &reg, const int jump);
  void run_command();

public:
  explicit Machine(const vector<string> program, const int c) noexcept;

  explicit Machine(const vector<string> program,
                   const ExtraHandlers extra_handlers) noexcept;

  void run_program();

  inline int a() const { return registers.at("a"); }
};

} // namespace Day12

#endif
