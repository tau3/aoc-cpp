#include "day23.hpp"
#include "day12.hpp"
#include <cstddef>

namespace Day23 {

void tgl(vector<string> &program, const size_t rip);

int solve(const vector<string> &input) {
  Day12::ExtraHandlers extra_handlers = {{"tgl", tgl}};

  Day12::Machine machine(input, extra_handlers);
  machine.run_program();

  return machine.a();
}

void tgl(vector<string> &program, const size_t rip) {}

} // namespace Day23
