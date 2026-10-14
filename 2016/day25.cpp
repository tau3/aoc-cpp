#include "day25.hpp"
#include "day12.hpp"
#include "day23.hpp"
#include "util.hpp"
#include <atomic>
#include <cassert>
#include <cctype>
#include <cstddef>
#include <future>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace Day25 {

using namespace std;

void out_impl(const Day12::Machine &machine, const vector<string> &program,
              const size_t &rip, string &out);

bool check_value(const vector<string> &input, const int a) {
  string out_stream;
  const Day12::ExtraHander out_handler =
      [&out_stream](const Day12::Machine &machine,
                    const vector<string> &program, const size_t &rip) {
        out_impl(machine, program, rip, out_stream);
      };
  const Day12::ExtraHandlers extra_handlers = {{"tgl", Day23::tgl},
                                               {"out", out_handler}};

  unordered_map<string, int> registers = Day12::Machine::default_registers();
  registers["a"] = a;
  Day12::Machine machine(input, registers, extra_handlers);

  while (out_stream.size() != 4) {
    machine.run_command();
  }
  return out_stream == "0101";
}

optional<int> run_task(const vector<string> &input, std::atomic_int &a,
                       std::atomic_bool &found) {
  while (!found) {
    const int val = a.fetch_add(1);
    assert(val > 0);
    if (check_value(input, val)) {
      found = true;
      return val;
    }
  }
  return nullopt;
}

int solve(const vector<string> &input) {
  std::atomic_int a = 1;
  std::atomic_bool found = false;

  vector<future<optional<int>>> tasks;
  for (size_t i = 0; i < 12; i++) {
    future<optional<int>> task = std::async(std::launch::async, run_task, input,
                                            std::ref(a), std::ref(found));
    tasks.push_back(std::move(task));
  }

  for (future<optional<int>> &task : tasks) {
    optional<int> result = task.get();
    if (result.has_value()) {
      return result.value();
    }
  }

  throw runtime_error("unreachable!");
}

void out_impl(const Day12::Machine &machine, const vector<string> &program,
              const size_t &rip, string &out) {
  const string &command = program[rip];

  const vector<string> tokens = util::split(command, " ");
  assert(tokens[0] == "out");

  const string &x = tokens[1];

  bool is_number = true;
  for (const char c : x) {
    if (!std::isdigit(c)) {
      is_number = false;
      break;
    }
  }

  if (is_number) {
    out += x;
  } else {
    if (x == "a") {
      out += to_string(machine.a());
    } else if (x == "b") {
      out += to_string(machine.b());
    } else if (x == "c") {
      out += to_string(machine.c());
    } else if (x == "d") {
      out += to_string(machine.d());
    }
  }
}

} // namespace Day25
